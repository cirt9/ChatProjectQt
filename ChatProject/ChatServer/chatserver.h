#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <QTcpServer>
#include <QTcpSocket>

class ChatServer : public QTcpServer
{
    Q_OBJECT

private:
    QSet<QTcpSocket *> clients;

private slots:
    void read();
    void disconnected();

protected:
    void incomingConnection(int socketfd);

public:
    ChatServer(QObject * parent = nullptr);
    ~ChatServer() {}

    void send(QString message, QTcpSocket * except = nullptr);

signals:
    void messageReceived(QString message);
    void infoOccurred(QString message);
};

#endif // CHATSERVER_H
