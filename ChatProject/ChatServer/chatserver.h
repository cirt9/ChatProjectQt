#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QMutableSetIterator>
#include <QSharedPointer>
#include <QDataStream>

class ChatServer : public QTcpServer
{
    Q_OBJECT

private:
    const static quint8 PACKET_ID_NORMAL_MSG = 0;
    const static quint8 PACKET_ID_NICKNAME = 1;
    const static quint8 PACKET_ID_SERVER_RESPONSE = 2;

    struct Client
    {
        QTcpSocket * socket;
        quint16 nextBlockSize;
        QString nickname;
    };

    QString serverName;
    QSet<QSharedPointer<Client> > clients;
    unsigned int lastClientIndex;
    bool duplicateNicknamesAllowed;

    void processPacket(QSharedPointer<Client> client, QDataStream & in, quint8 packetId = 0);
    void manageMessage(QSharedPointer<Client> client, QDataStream & in);
    void setClientNickname(QSharedPointer<Client> client, QDataStream & in);
    void sendResponse(QSharedPointer<Client> client, QString response);
    void sendNicknameToClient(QSharedPointer<Client> client);

    void flushClientSocket(QTcpSocket * clientSocket);
    QSharedPointer<Client> findClient(QTcpSocket * socket);
    bool isNicknameDuplicate(QString & nickname);
    void reset();

private slots:
    void read();
    void disconnected();

protected:
    void incomingConnection(int socketfd);

public:
    const static QString DEFAULT_SERVER_NAME;

    ChatServer(QObject * parent = nullptr);
    ~ChatServer() {}

    void spreadMessage(QString nickname, QString message, QTcpSocket * except = nullptr);
    void closeServer();

    void allowDuplicateNicknames(bool allowed);
    void setServerName(const QString & name);
    QString getServerName() const;
    QStringList getClientsNames() const;

signals:
    void messageReceived(QString nickname, QString message);
    void newClientConnected();
    void clientDisconnected(QString nickname);

    void nameChanged(QString message);
    void nameCurrentlyUsed(QString message);

private:
    void unpackToDataStream(QDataStream &){}

    template<typename T, typename... Args>
    void unpackToDataStream(QDataStream & out, T value, Args... args)
    {
        out << value;
        unpackToDataStream(out, args...);
    }

    template<typename... Args>
    void send(quint8 packetId, QTcpSocket * socket, Args... args)
    {
        QByteArray block;
        QDataStream out(&block, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_4_6);

        out << quint16(0) << packetId;
        unpackToDataStream(out, args...);
        out.device()->seek(0);
        out << quint16(block.size() - sizeof(quint16));
        socket->write(block);
    }
};

#endif // CHATSERVER_H
