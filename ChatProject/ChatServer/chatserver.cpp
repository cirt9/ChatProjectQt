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
    QTcpSocket * clientSocket = (QTcpSocket *)sender();

    if(clientSocket->canReadLine())
    {
        bool isInteger;
        int messageId = QString::fromUtf8(clientSocket->readLine()).trimmed().toInt(&isInteger);

        if(isInteger)
            processPacket(clientSocket, messageId);
        else
            flushClientSocket(clientSocket);
    }
}

void ChatServer::processPacket(QTcpSocket * clientSocket, int packetId)
{
    switch(packetId)
    {
    case PACKET_NORMAL_MSG_ID: manageMessage(clientSocket); break;
    case PACKET_NICKNAME_CHANGE_ID: setClientNickname(clientSocket); break;

    default: break;
    }
    flushClientSocket(clientSocket);
}

void ChatServer::manageMessage(QTcpSocket * clientSocket)
{
    QString nickname;
    for(auto client : clients)
    {
        if(client->socket == clientSocket)
        {
            nickname = client->nickname;
            break;
        }
    }

    while(clientSocket->canReadLine())
    {
        QString line = QString::fromUtf8(clientSocket->readLine()).trimmed();
        emit messageReceived(nickname, line);
        qDebug() << line;

        send(nickname, line, clientSocket);
    }
}

void ChatServer::send(QString nickname, QString message, QTcpSocket * except)
{
    for(auto client : clients)
    {
        if(client->socket != except)
        {
            client->socket->write((nickname + "\n" + message).trimmed().toUtf8());
            client->socket->flush();
            client->socket->waitForBytesWritten(30000);
        }
    }
}

void ChatServer::setClientNickname(QTcpSocket * clientSocket)
{
    while(clientSocket->canReadLine())
    {
        QString newNickname = QString::fromUtf8(clientSocket->readLine()).trimmed();
        qDebug() << newNickname;

        for(auto client : clients)
        {
            if(client->socket == clientSocket)
            {
                client->nickname = newNickname;
                break;
            }
        }
    }
}

void ChatServer::flushClientSocket(QTcpSocket * clientSocket)
{
    if(clientSocket->canReadLine())
        QByteArray data = clientSocket->readAll();
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
