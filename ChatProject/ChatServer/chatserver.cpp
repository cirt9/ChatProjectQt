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

        //message sending Server -> client test
        send(line, client);
        /*client->write(QString("Test message").toUtf8());
        client->flush();
        client->waitForBytesWritten(30000);*/
        //
    }
}

void ChatServer::disconnected()
{
    QTcpSocket * client = (QTcpSocket *)sender();
    qDebug() << "Client disconnected: " << client->peerAddress().toString();

    clients.remove(client);
}

void ChatServer::send(QString message, QTcpSocket * except)
{
    qDebug() << clients.size();
    QSetIterator<QTcpSocket *> i(clients);
    while(i.hasNext())
    {
        if(i.next() != except)
        {
            i.next()->write(message.trimmed().toUtf8());
            i.next()->flush();
            i.next()->waitForBytesWritten(30000);
        }
    }
}
