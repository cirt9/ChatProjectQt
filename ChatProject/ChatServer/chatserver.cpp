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

    qDebug() << "New client from: " << client->peerAddress().toString();

    connect(client, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(client, SIGNAL(disconnected()), this, SLOT(disconnected()));
}

void ChatServer::readyRead()
{
    QTcpSocket * client = (QTcpSocket *)sender();

    qDebug() << "reading";

    while(client->canReadLine())
    {
        QString line = QString::fromUtf8(client->readLine()).trimmed();
        qDebug() << line;
        //transfer message to chat widget
    }
}

void ChatServer::disconnected()
{
    QTcpSocket * client = (QTcpSocket *)sender();
    qDebug() << "Client disconnected: " << client->peerAddress().toString();

    clients.remove(client);
}
