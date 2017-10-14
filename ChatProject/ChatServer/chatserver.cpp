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

    while(client->canReadLine())
    {
        QString line = QString::fromUtf8(client->readLine()).trimmed();
        emit messageReceived(line);
        qDebug() << line;
        //transfer message to chat widget

        //message sending Server -> client test
        client->write(QString("Test message").toUtf8());
        client->flush();
        client->waitForBytesWritten(30000);
        //
    }
}

void ChatServer::disconnected()
{
    QTcpSocket * client = (QTcpSocket *)sender();
    qDebug() << "Client disconnected: " << client->peerAddress().toString();

    clients.remove(client);
}
