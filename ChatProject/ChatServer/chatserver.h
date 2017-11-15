#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QMutableSetIterator>

class ChatServer : public QTcpServer
{
    Q_OBJECT

private:

    struct Client
    {
        QTcpSocket * socket;
        QString nickname;
    };

    QSet<Client *> clients;

    void processPacket(QTcpSocket * client, int id = 0);

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
