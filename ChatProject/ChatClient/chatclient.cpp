#include "chatclient.h"

ChatClient::ChatClient(QObject * parent) : QObject(parent)
{
    clientSocket = new QTcpSocket(this);
    nextBlockSize = 0;

    connect(clientSocket, SIGNAL(error(QAbstractSocket::SocketError)), this,
            SLOT(lookForErrors(QAbstractSocket::SocketError)));
    connect(clientSocket, SIGNAL(readyRead()), this, SLOT(read()));
}

bool ChatClient::connectToServer(QString ip, int portNumber)
{
    clientSocket->connectToHost(ip, quint16(portNumber));

    if(clientSocket->waitForConnected())
    {
        nextBlockSize = 0;
        return true;
    }
    else
        return false;
}

void ChatClient::disconnectFromServer()
{
    clientSocket->disconnectFromHost();
}

void ChatClient::read()
{
    QDataStream in(clientSocket);
    in.setVersion(QDataStream::Qt_4_6);

    if(nextBlockSize == 0)
    {
        if(clientSocket->bytesAvailable() < sizeof(quint16))
            return;
        in >> nextBlockSize;
    }

    if(clientSocket->bytesAvailable() < nextBlockSize)
        return;

    quint8 packetId;
    in >> packetId;
    processPacket(in, packetId);

    nextBlockSize = 0;
}

void ChatClient::processPacket(QDataStream & in, quint8 packetId)
{
    switch(packetId)
    {
    case PACKET_ID_NORMAL_MSG: manageMessage(in); break;
    case PACKET_ID_SERVER_RESPONSE: manageServerResponse(in); break;

    default: break;
    }
    flushSocket();
}

void ChatClient::manageMessage(QDataStream & in)
{
    QString nickname;
    QString message;
    in >> nickname >> message;

    emit messageReceived(nickname, message);
}

void ChatClient::manageServerResponse(QDataStream & in)
{
    QString response;
    in >> response;

    emit serverResponded(response);
}

void ChatClient::sendMessage(QString message)
{
    send(PACKET_ID_NORMAL_MSG, message);
}

void ChatClient::setNickname(QString nickname)
{
    send(PACKET_ID_NICKNAME_CHANGE, nickname);
}

void ChatClient::send(quint8 packetId, QString message)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_6);

    out << quint16(0) << packetId << message;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    clientSocket->write(block);
}

void ChatClient::flushSocket()
{
    if(clientSocket->bytesAvailable())
        clientSocket->readAll();
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
