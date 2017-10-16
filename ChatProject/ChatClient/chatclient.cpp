#include "chatclient.h"
#include <QDebug>

ChatClient::ChatClient(QObject * parent) : QObject(parent)
{
    clientSocket = new QTcpSocket(this);

    connect(clientSocket, SIGNAL(error(QAbstractSocket::SocketError)), this,
            SLOT(displayError(QAbstractSocket::SocketError)));
    connect(clientSocket, SIGNAL(readyRead()), this, SLOT(readyRead()));    
}

void ChatClient::connectToHost(QString ip, int portNumber)
{
    clientSocket->connectToHost(ip, quint16(portNumber));

    if(clientSocket->waitForConnected())
        qDebug() << "Connected";
    else
        qDebug() << "Couldn't connect";
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

void ChatClient::readyRead()
{
    QByteArray data = clientSocket->readAll();
    QString dataString(data);

    qDebug() << dataString;
}
