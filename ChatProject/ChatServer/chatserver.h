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
    const static int NORMAL_MSG = 0;
    const static int NICKNAME_CHANGE = 1;

    struct Client
    {
        QTcpSocket * socket;
        QString nickname;
    };

    QSet<QSharedPointer<Client> > clients;

    void processPacket(QTcpSocket * clientSocket, int packetId = 0);
    void manageMessage(QTcpSocket * clientSocket);
    void changeClientNickname(QTcpSocket * clientSocket);

private slots:
    void read();
    void disconnected();

protected:
    void incomingConnection(int socketfd);

public:
    ChatServer(QObject * parent = nullptr);
    ~ChatServer() {}

    void send(QString message, QTcpSocket * except = nullptr);
    void closeServer();

signals:
    void messageReceived(QString message);
    void infoOccurred(QString message);
};

#endif // CHATSERVER_H
