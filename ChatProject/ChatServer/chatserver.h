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
    const static quint8 PACKET_ID_NICKNAME_CHANGE = 1;
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
    bool duplicateClientNamesAllowed;

    void processPacket(QSharedPointer<Client> client, QDataStream & in, quint8 packetId = 0);
    void manageMessage(QSharedPointer<Client> client, QDataStream & in);
    void setClientNickname(QSharedPointer<Client> client, QDataStream & in);

    void sendResponse(QSharedPointer<Client> client, QString response);
    void flushClientSocket(QTcpSocket * clientSocket);
    QSharedPointer<Client> findClient(QTcpSocket * socket);

private slots:
    void read();
    void disconnected();

protected:
    void incomingConnection(int socketfd);

public:
    ChatServer(QObject * parent = nullptr);
    ~ChatServer() {}

    void send(QString nickname, QString message, QTcpSocket * except = nullptr);
    void closeServer();

    void allowDuplicateClientNames(bool allowed);
    void setServerName(QString name);
    QString getServerName() const;
    QStringList getClientsNames() const;

signals:
    void messageReceived(QString nickname, QString message);
    void newClientConnected();
    void clientDisconnected(QString nickname);
};

#endif // CHATSERVER_H
