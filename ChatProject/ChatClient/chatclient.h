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

    bool isConnected() const;

public slots:
    bool connectToServer(QString ip, int portNumber);
    void disconnectFromServer();
    void send(QString message);

signals:
    void messageReceived(QString message);
    void errorOccurred(QString error);
};

#endif // CHATCLIENT_H
