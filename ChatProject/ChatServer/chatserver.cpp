#include "chatserver.h"
#include <QDebug>

ChatServer::ChatServer(QObject * parent) : QTcpServer(parent)
{

}

void ChatServer::incomingConnection(int socketfd)
{
    Client * client = new Client();
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
    QTcpSocket * client = (QTcpSocket *)sender();

    if(client->canReadLine())
    {
        int messageId = QString::fromUtf8(client->readLine()).trimmed().toInt();
        processPacket(client, messageId);
    }
}

void ChatServer::processPacket(QTcpSocket * client, int id)
{
    switch (id)
    {
    case 0:
            while(client->canReadLine())
            {
                QString line = QString::fromUtf8(client->readLine()).trimmed();
                emit messageReceived(line);
                qDebug() << line;

                send(line, client);
            }
        break;

    case 1:
            while(client->canReadLine())
            {
                QString stub = QString::fromUtf8(client->readLine()).trimmed();
            }
            qDebug() << "case 1";
        break;
    default:
        break;
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

void ChatServer::closeServer()
{
    for(auto client : clients)
    {
        disconnect(client->socket, SIGNAL(readyRead()), this, SLOT(read()));
        disconnect(client->socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
        client->socket->disconnectFromHost();
        client->socket->deleteLater();
        delete client;
    }
    clients.clear();
    close();
}

void ChatServer::disconnected()
{
    QTcpSocket * client = (QTcpSocket *)sender();

    //
    qDebug() << "Client disconnected: " << client->peerAddress().toString();
    emit infoOccurred("Client disconnected: " + client->peerAddress().toString());
    //
    client->deleteLater();

    QMutableSetIterator<Client *> i(clients);
     while (i.hasNext())
     {
         Client * clientData = i.next();
         if(clientData->socket == client)
         {
             delete clientData;
             i.remove();
             break;
         }
     }
}
