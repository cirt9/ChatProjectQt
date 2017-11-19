#include "chatclient.h"
#include <QDebug>

ChatClient::ChatClient(QObject * parent) : QObject(parent)
{
    clientSocket = new QTcpSocket(this);

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

void ChatClient::sendMessage(QString message)
{
    send(NORMAL_MESSAGE_ID, message);
}

void ChatClient::setNickname(QString nickname)
{
    send(NICKNAME_CHANGE_ID, nickname);
}

void ChatClient::send(int messageId, QString message)
{
    message = message.trimmed();

    clientSocket->write((QString::number(messageId) + "\n" + message + "\n").toUtf8());
}

void ChatClient::lookForErrors(QAbstractSocket::SocketError socketError)
{
    if(socketError == QAbstractSocket::RemoteHostClosedError)
    {
        lastError = "The connection with remote host was lost.";
        emit unscheduledDisconnection();
    }

    else if(socketError == QAbstractSocket::HostNotFoundError)
        lastError = "The host was not found. Check the host name and port settings.";

    else if(socketError == QAbstractSocket::ConnectionRefusedError)
        lastError = "The connection was refused by the peer.";

    else if(socketError == QAbstractSocket::SocketAccessError)
        lastError = "The application lacks the required privileges.";

    else if(socketError == QAbstractSocket::NetworkError)
        lastError = "An error occurred with the network.";

    else
        lastError = "The following error ocurred: " + clientSocket->errorString();

    emit errorOccurred(lastError);
}

void ChatClient::read()
{
    QByteArray data = clientSocket->readAll();
    QString dataString(data);
    qDebug() << dataString;

    int index = dataString.indexOf("\n");

    QString nickname = dataString.left(index);
    QString message = dataString.mid(index);

    emit messageReceived(nickname, message);
}

bool ChatClient::isConnected() const
{
    return clientSocket->state() == QTcpSocket::ConnectedState;
}

void ChatClient::enableKeepAliveOption()
{
    clientSocket->setSocketOption(QAbstractSocket::KeepAliveOption, 1);
}

QString ChatClient::getLastError() const
{
    return lastError;
}
