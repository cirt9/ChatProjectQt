#include "chatclient.h"

ChatClient::ChatClient(QObject * parent) : QObject(parent)
{
    clientSocket = new QTcpSocket(this);
}

void ChatClient::connect(QString ip, int portNumber)
{
    clientSocket->connectToHost(ip, quint16(portNumber));
}
