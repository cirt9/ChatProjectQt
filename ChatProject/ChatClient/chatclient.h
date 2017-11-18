#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <QObject>
#include <QTcpSocket>

class ChatClient : public QObject
{
    Q_OBJECT

private:
    const static int NORMAL_MESSAGE_ID = 0;
    const static int NICKNAME_CHANGE_ID = 1;

    QTcpSocket * clientSocket;
    QString lastError;

    void send(int messageId, QString message);

private slots:
    void lookForErrors(QAbstractSocket::SocketError socketError);
    void read();

public:
    explicit ChatClient(QObject * parent = nullptr);
    ~ChatClient() {}

    bool isConnected() const;
    void enableKeepAliveOption();
    QString getLastError() const;

public slots:
    bool connectToServer(QString ip, int portNumber);
    void disconnectFromServer();
    void sendMessage(QString message);
    void setNickname(QString nickname);

signals:
    void messageReceived(QString message);
    void errorOccurred(QString error);
    void unscheduledDisconnection();
};

#endif // CHATCLIENT_H
