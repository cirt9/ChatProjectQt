#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <QObject>
#include <QTcpSocket>

class ChatClient : public QObject
{
    Q_OBJECT

private:
    QTcpSocket * clientSocket;

private slots:
    void lookForErrors(QAbstractSocket::SocketError socketError);
    void read();

public:
    explicit ChatClient(QObject * parent = nullptr);
    ~ChatClient() {}

public slots:
    void connectToHost(QString ip, int portNumber);
    void send(QString message);

signals:
    void messageReceived(QString message);
    void errorOccurred(QString error);
    void infoOccurred(QString info);
};

#endif // CHATCLIENT_H
