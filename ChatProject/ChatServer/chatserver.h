#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QMutableSetIterator>
#include <QSharedPointer>

class ChatServer : public QTcpServer
{
    Q_OBJECT

private:
    const static int PACKET_NORMAL_MSG_ID = 0;
    const static int PACKET_NICKNAME_CHANGE_ID = 1;

    QString serverName;

    struct Client
    {
        QTcpSocket * socket;
        QString nickname;
    };

    QSet<QSharedPointer<Client> > clients;

    void processPacket(QTcpSocket * clientSocket, int packetId = 0);
    void manageMessage(QTcpSocket * clientSocket);
    void setClientNickname(QTcpSocket * clientSocket);
    void flushClientSocket(QTcpSocket * clientSocket);

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
