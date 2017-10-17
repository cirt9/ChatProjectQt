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
    void displayError(QAbstractSocket::SocketError socketError);

    void readyRead();

public:
    explicit ChatClient(QObject * parent = nullptr);
    ~ChatClient() {}

public slots:
    void connectToHost(QString ip, int portNumber);
    void send(QString message);

signals:
    void messageReceived(QString message);
};

#endif // CHATCLIENT_H
