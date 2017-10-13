#include "chatclient.h"
#include <QDebug>

ChatClient::ChatClient(QObject * parent) : QObject(parent)
{
    clientSocket = new QTcpSocket(this);

    connect(clientSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));
}

void ChatClient::connectToHost(QString ip, int portNumber)
{
    clientSocket->connectToHost(ip, quint16(portNumber));
}

void ChatClient::send(QString message)
{
    message = message.trimmed();
    clientSocket->write(QString(message + "\n").toUtf8());
}

void ChatClient::displayError(QAbstractSocket::SocketError socketError)
{
    if(socketError == QAbstractSocket::RemoteHostClosedError)
        qDebug() << "Remote host closed the connection.";

    else if(socketError == QAbstractSocket::HostNotFoundError)
        qDebug() << "The host was not found. Check the host name and port settings";

    else if(socketError == QAbstractSocket::ConnectionRefusedError)
        qDebug() << "The connection was refused by the peer.";

    else
        qDebug() << "The following error ocurred: " + clientSocket->errorString();
}
