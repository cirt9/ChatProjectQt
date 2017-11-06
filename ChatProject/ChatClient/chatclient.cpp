#include "chatclient.h"
#include <QDebug>

ChatClient::ChatClient(QObject * parent) : QObject(parent)
{
    clientSocket = new QTcpSocket(this);
    clientSocket->setSocketOption(QAbstractSocket::KeepAliveOption, 1);

    connect(clientSocket, SIGNAL(error(QAbstractSocket::SocketError)), this,
            SLOT(lookForErrors(QAbstractSocket::SocketError)));
    connect(clientSocket, SIGNAL(readyRead()), this, SLOT(read()));
}

bool ChatClient::connectToServer(QString ip, int portNumber)
{
    clientSocket->connectToHost(ip, quint16(portNumber));

    if(clientSocket->waitForConnected())
        return true;
    else
        return false;
}

void ChatClient::disconnectFromServer()
{
    clientSocket->disconnectFromHost();
}

void ChatClient::send(QString message)
{
    message = message.trimmed();
    clientSocket->write(QString(message + "\n").toUtf8());
}

void ChatClient::lookForErrors(QAbstractSocket::SocketError socketError)
{
    if(socketError == QAbstractSocket::RemoteHostClosedError)
        emit errorOccurred("The connection with remote host was lost.");

    else if(socketError == QAbstractSocket::HostNotFoundError)
        emit errorOccurred("The host was not found. Check the host name and port settings");

    else if(socketError == QAbstractSocket::ConnectionRefusedError)
        emit errorOccurred("The connection was refused by the peer");

    else
        emit errorOccurred("The following error ocurred: " + clientSocket->errorString());
}

void ChatClient::read()
{
    QByteArray data = clientSocket->readAll();
    QString dataString(data);

    emit messageReceived(dataString);
    qDebug() << dataString;
}

bool ChatClient::isConnected() const
{
    return clientSocket->state() == QTcpSocket::ConnectedState;
}
