#include "chatserver.h"
#include <QDebug>

ChatServer::ChatServer(QObject * parent) : QTcpServer(parent)
{

}

void ChatServer::incomingConnection(int socketfd)
{
    QSharedPointer<Client> client = QSharedPointer<Client>(new Client());
    client->socket = new QTcpSocket(this);
    client->socket->setSocketDescriptor(socketfd);
    client->nickname = QString("Nickname"+clients.size());
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

        if(isInteger && messageId >= PACKET_MIN_ID && messageId <= PACKET_MAX_ID)
            processPacket(clientSocket, messageId);
        else
            QByteArray data = clientSocket->readAll();
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

}

void ChatServer::manageMessage(QTcpSocket * clientSocket)
{
    while(clientSocket->canReadLine())
    {
        QString line = QString::fromUtf8(clientSocket->readLine()).trimmed();
        emit messageReceived(line);
        qDebug() << line;

        send(line, clientSocket);
    }
}

void ChatServer::send(QString message, QTcpSocket * except)
{
    for(auto client : clients)
    {
        if(client->socket != except)
        {
            client->socket->write(message.trimmed().toUtf8());
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
