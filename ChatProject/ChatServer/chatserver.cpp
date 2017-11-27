#include "chatserver.h"
#include <QDebug>

ChatServer::ChatServer(QObject * parent) : QTcpServer(parent)
{
    setServerName("Server");
}

void ChatServer::incomingConnection(int socketfd)
{
    QSharedPointer<Client> client = QSharedPointer<Client>(new Client());
    client->socket = new QTcpSocket(this);
    client->socket->setSocketDescriptor(socketfd);
    client->nextBlockSize = 0;
    client->nickname = QString("Client") + QString::number(clients.size());
    clients.insert(client);

    //
    qDebug() << "New client from: " + client->socket->peerAddress().toString();
    emit infoOccurred("New client from: " + client->socket->peerAddress().toString());
    //

    connect(client->socket, SIGNAL(readyRead()), this, SLOT(read()));
    connect(client->socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
}

void ChatServer::read()
{
    QSharedPointer<Client> client = findClient((QTcpSocket *)sender());

    if(client == nullptr)
        return;

    QDataStream in(client->socket);
    in.setVersion(QDataStream::Qt_4_6);

    if(client->nextBlockSize == 0)
    {
        if(client->socket->bytesAvailable() < sizeof(quint16))
            return;
        in >> client->nextBlockSize;
    }

    if(client->socket->bytesAvailable() < client->nextBlockSize)
        return;

    quint8 packetId;
    in >> packetId;
    qDebug() << packetId;
    processPacket(client, in, packetId);
    client->nextBlockSize = 0;
}

void ChatServer::processPacket(QSharedPointer<Client> client, QDataStream & in, quint8 packetId)
{
    switch(packetId)
    {
    case PACKET_ID_NORMAL_MSG: manageMessage(client, in); break;
    case PACKET_ID_NICKNAME_CHANGE: setClientNickname(client, in); break;

    default: flushClientSocket(client->socket); break;
    }
}

void ChatServer::manageMessage(QSharedPointer<Client> client, QDataStream & in)
{
    QString message;
    in >> message;

    emit messageReceived(client->nickname, message);
    qDebug() << message;

    send(client->nickname, message, client->socket);
}

void ChatServer::setClientNickname(QSharedPointer<Client> client, QDataStream & in)
{
    QString newNickname;
    in >> newNickname;

    client->nickname = newNickname;

    qDebug() << newNickname;
}

void ChatServer::send(QString nickname, QString message, QTcpSocket * except)
{
    for(auto client : clients)
    {
        if(client->socket != except)
        {
            QByteArray block;
            QDataStream out(&block, QIODevice::WriteOnly);
            out.setVersion(QDataStream::Qt_4_6);

            out << quint16(0) << nickname << message;
            out.device()->seek(0);
            out << quint16(block.size() - sizeof(quint16));
            client->socket->write(block);
        }
    }
}

void ChatServer::flushClientSocket(QTcpSocket * clientSocket)
{
    if(clientSocket->bytesAvailable())
        clientSocket->readAll();
}

void ChatServer::closeServer()
{
    for(auto client : clients)
    {
        disconnect(client->socket, SIGNAL(readyRead()), this, SLOT(read()));
        disconnect(client->socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
        client->socket->disconnectFromHost();
        client->socket->deleteLater();
    }
    clients.clear();
    close();
    setServerName("Server");
}

void ChatServer::disconnected()
{
    QTcpSocket * clientSocket = (QTcpSocket *)sender();

    //
    qDebug() << "Client disconnected: " << clientSocket->peerAddress().toString();
    emit infoOccurred("Client disconnected: " + clientSocket->peerAddress().toString());
    //

    QMutableSetIterator<QSharedPointer<Client> > i(clients);
    while(i.hasNext())
    {
        if(i.next()->socket == clientSocket)
        {
            clientSocket->deleteLater();
            i.remove();
            break;
        }
    }
}

void ChatServer::setServerName(QString name)
{
    serverName = name;
}

QString ChatServer::getServerName() const
{
    return serverName;
}

QStringList ChatServer::getClientsNames() const
{
    QStringList clientsNames;

    for(auto client : clients)
        clientsNames << client->nickname;

    return clientsNames;
}

QSharedPointer<ChatServer::Client> ChatServer::findClient(QTcpSocket * socket)
{
    for(auto client : clients)
    {
        if(socket == client->socket)
            return client;
    }
    return nullptr;
}
