#include "chatclient.h"
#include <QDebug>

ChatClient::ChatClient(QObject * parent) : QObject(parent)
{
    clientSocket = new QTcpSocket(this);

    connect(clientSocket, SIGNAL(error(QAbstractSocket::SocketError)), this,
            SLOT(lookForErrors(QAbstractSocket::SocketError)));
    connect(clientSocket, SIGNAL(readyRead()), this, SLOT(read()));
}

void ChatClient::connectToHost(QString ip, int portNumber)
{
    clientSocket->connectToHost(ip, quint16(portNumber));

    if(clientSocket->waitForConnected())
    {
        emit infoOccurred("Connected");
        qDebug() << "Connected";
    }
    else
    {
        emit infoOccurred("Couldn't connect");
        qDebug() << "Couldn't connect";
    }
}

void ChatClient::send(QString message)
{
    message = message.trimmed();
    clientSocket->write(QString(message + "\n").toUtf8());
}

void ChatClient::lookForErrors(QAbstractSocket::SocketError socketError)
{
    if(socketError == QAbstractSocket::RemoteHostClosedError)
    {
        emit errorOccurred("Remote host closed the connection");
        qDebug() << "Remote host closed the connection.";
    }

    else if(socketError == QAbstractSocket::HostNotFoundError)
    {
        emit errorOccurred("The host was not found. Check the host name and port settings");
        qDebug() << "The host was not found. Check the host name and port settings";
    }

    else if(socketError == QAbstractSocket::ConnectionRefusedError)
    {
        emit errorOccurred("The connection was refused by the peer");
        qDebug() << "The connection was refused by the peer.";
    }

    else
    {
        emit errorOccurred("The following error ocurred: " + clientSocket->errorString());
        qDebug() << "The following error ocurred: " + clientSocket->errorString();
    }
}

void ChatClient::read()
{
    QByteArray data = clientSocket->readAll();
    QString dataString(data);

    emit messageReceived(dataString);
    qDebug() << dataString;
}
