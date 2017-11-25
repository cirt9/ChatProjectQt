#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QDataStream>

class ChatClient : public QObject
{
    Q_OBJECT

private:
    const static quint8 NORMAL_MESSAGE_ID = 0;
    const static quint8 NICKNAME_CHANGE_ID = 1;

    QTcpSocket * clientSocket;
    quint16 nextBlockSize;
    QString lastError;

    void send(quint8 messageId, QString message);

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
    void messageReceived(QString nickname, QString message);
    void errorOccurred(QString error);
    void unscheduledDisconnection();
};

#endif // CHATCLIENT_H
