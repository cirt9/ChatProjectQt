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
    const static quint8 PACKET_NORMAL_MSG_ID = 0;
    const static quint8 PACKET_NICKNAME_CHANGE_ID = 1;

    QString serverName;

    struct Client
    {
        QTcpSocket * socket;
        QString nickname;
        quint16 nextBlockSize;
    };

    QSet<QSharedPointer<Client> > clients;

    void processPacket(QSharedPointer<Client> client, QDataStream & in, quint8 packetId = 0);
    void manageMessage(QSharedPointer<Client> client, QDataStream & in);
    void setClientNickname(QSharedPointer<Client> client, QDataStream & in);

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

    void setServerName(QString name);
    QString getServerName() const;

signals:
    void messageReceived(QString nickname, QString message);
    void infoOccurred(QString message);
};

#endif // CHATSERVER_H
