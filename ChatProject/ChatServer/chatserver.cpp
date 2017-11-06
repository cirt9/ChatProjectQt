#include "chatserver.h"
#include <QDebug>

ChatServer::ChatServer(QObject * parent) : QTcpServer(parent)
{

}

void ChatServer::incomingConnection(int socketfd)
{
    QTcpSocket * client = new QTcpSocket(this);
    client->setSocketDescriptor(socketfd);
    clients.insert(client);

    //
    qDebug() << "New client from: " + client->peerAddress().toString();
    emit infoOccurred("New client from: " + client->peerAddress().toString());
    //

    connect(client, SIGNAL(readyRead()), this, SLOT(read()));
    connect(client, SIGNAL(disconnected()), this, SLOT(disconnected()));
}

void ChatServer::read()
{
    QTcpSocket * client = (QTcpSocket *)sender();

    while(client->canReadLine())
    {
        QString line = QString::fromUtf8(client->readLine()).trimmed();
        emit messageReceived(line);
        qDebug() << line;

        send(line, client);
    }
}

void ChatServer::send(QString message, QTcpSocket * except)
{
    for(auto client : clients)
    {
        if(client != except)
        {
            client->write(message.trimmed().toUtf8());
            client->flush();
            client->waitForBytesWritten(30000);
        }
    }
}

void ChatServer::closeServer()
{
    for(auto client : clients)
    {
        disconnect(client, SIGNAL(readyRead()), this, SLOT(read()));
        disconnect(client, SIGNAL(disconnected()), this, SLOT(disconnected()));
        client->disconnectFromHost();
        client->deleteLater();
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

    clients.remove(client);
}
