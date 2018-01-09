#include "chatserver.h"
const QString ChatServer::DEFAULT_SERVER_NAME = QString("Server");

ChatServer::ChatServer(QObject * parent) : QTcpServer(parent)
{
    reset();
}

void ChatServer::incomingConnection(int socketfd)
{
    QSharedPointer<Client> client = QSharedPointer<Client>(new Client());
    client->socket = new QTcpSocket(this);
    client->socket->setSocketDescriptor(socketfd);
    client->nextBlockSize = 0;
    client->nickname = generateClientNickname();
    clients.insert(client);
    sendNicknameToClient(client);

    emit newClientConnected();
    connect(client->socket, SIGNAL(readyRead()), this, SLOT(read()));
    connect(client->socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
}

QString ChatServer::generateClientNickname()
{
    if(duplicateNicknamesAllowed)
        return QString("Client") + QString::number(lastClientIndex++);
    else
    {
        while(true)
        {
            QString generatedNickname = QString("Client") + QString::number(lastClientIndex++);
            bool alreadyReserved = false;

            for(auto client : clients)
            {
               if(client->nickname == generatedNickname)
               {
                   alreadyReserved = true;
                   break;
               }
            }
            if(!alreadyReserved)
                return generatedNickname;
        }
    }
}

void ChatServer::read()
{
    QSharedPointer<Client> client = findClient((QTcpSocket *)sender());

    if(client == nullptr)
        return;

    QDataStream in(client->socket);
    in.setVersion(QDataStream::Qt_4_6);

    if(client->nextBlockSize == 0)
    {
        if(client->socket->bytesAvailable() < sizeof(quint16))
            return;
        in >> client->nextBlockSize;
    }

    if(client->socket->bytesAvailable() < client->nextBlockSize)
        return;

    quint8 packetId;
    in >> packetId;

    processPacket(client, in, packetId);
    client->nextBlockSize = 0;
}

void ChatServer::processPacket(QSharedPointer<Client> client, QDataStream & in, quint8 packetId)
{
    switch(packetId)
    {
    case PACKET_ID_NORMAL_MSG: manageMessage(client, in); break;
    case PACKET_ID_NICKNAME: setClientNickname(client, in); break;

    default: break;
    }
    flushClientSocket(client->socket);
}

void ChatServer::manageMessage(QSharedPointer<Client> client, QDataStream & in)
{
    QString message;
    in >> message;

    emit messageReceived(client->nickname, message);
    spreadMessage(client->nickname, message, client->socket);
}

void ChatServer::setClientNickname(QSharedPointer<Client> client, QDataStream & in)
{
    QString newNickname;
    in >> newNickname;

    if(duplicateNicknamesAllowed)
    {
        client->nickname = newNickname;
        sendNicknameToClient(client);
    }

    else
    {
        if(isNicknameDuplicate(newNickname))
            sendResponse(client, "Nickname has not been changed because it is already reserved.");
        else
        {
            client->nickname = newNickname;
            sendNicknameToClient(client);
        }
    }
}

void ChatServer::sendResponse(QSharedPointer<Client> client, const QString & response)
{
    send(PACKET_ID_SERVER_RESPONSE, client->socket, response);
}

void ChatServer::sendNicknameToClient(QSharedPointer<ChatServer::Client> client)
{
    send(PACKET_ID_NICKNAME, client->socket, client->nickname);
}

void ChatServer::spreadMessage(const QString & nickname, const QString & message, QTcpSocket * except)
{
    for(auto client : clients)
    {
        if(client->socket != except)
            send(PACKET_ID_NORMAL_MSG, client->socket, nickname, message);
    }
}

void ChatServer::flushClientSocket(QTcpSocket * clientSocket)
{
    if(clientSocket->bytesAvailable())
        clientSocket->readAll();
}

void ChatServer::closeServer()
{
    for(auto client : clients)
    {
        disconnect(client->socket, SIGNAL(readyRead()), this, SLOT(read()));
        disconnect(client->socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
        client->socket->disconnectFromHost();
        client->socket->deleteLater();
    }
    clients.clear();
    close();
    reset();
}

void ChatServer::disconnected()
{
    QTcpSocket * clientSocket = (QTcpSocket *)sender();

    QMutableSetIterator<QSharedPointer<Client> > i(clients);
    while(i.hasNext())
    {
        if(i.next()->socket == clientSocket)
        {
            emit clientDisconnected(i.value()->nickname);
            clientSocket->deleteLater();
            i.remove();
            break;
        }
    }
}

void ChatServer::allowDuplicateNicknames(bool allowed)
{
    duplicateNicknamesAllowed = allowed;
}

void ChatServer::setServerName(const QString & name)
{
    if(name == serverName)
        emit nameCurrentlyUsed("Server is currently using this name.");
    else
    {
        serverName = name;
        emit nameChanged("Server successfully changed its name to: "+serverName);
    }
}

QString ChatServer::getServerName() const
{
    return serverName;
}

QStringList ChatServer::getClientsNames() const
{
    QStringList clientsNames;

    for(auto client : clients)
        clientsNames << client->nickname;

    return clientsNames;
}

QSharedPointer<ChatServer::Client> ChatServer::findClient(QTcpSocket * socket)
{
    for(auto client : clients)
    {
        if(socket == client->socket)
            return client;
    }
    return nullptr;
}

bool ChatServer::isNicknameDuplicate(const QString & nickname)
{
    if(nickname == serverName)
        return true;

    for(auto client : clients)
    {
        if(client->nickname == nickname)
            return true;
    }
    return false;
}

void ChatServer::reset()
{
    serverName = DEFAULT_SERVER_NAME;
    lastClientIndex = 0;
    allowDuplicateNicknames(false);

    emit serverReseted();
}
