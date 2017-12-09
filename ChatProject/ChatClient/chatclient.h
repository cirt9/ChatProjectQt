#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QDataStream>

class ChatClient : public QObject
{
    Q_OBJECT

private:
    const static quint8 PACKET_ID_NORMAL_MSG = 0;
    const static quint8 PACKET_ID_NICKNAME = 1;
    const static quint8 PACKET_ID_SERVER_RESPONSE = 2;

    QTcpSocket * clientSocket;
    quint16 nextBlockSize;
    QString lastError;

    void processPacket(QDataStream & in, quint8 packetId = 0);
    void manageMessage(QDataStream & in);
    void manageServerResponse(QDataStream & in);
    void readNewNickname(QDataStream & in);
    void send(quint8 packetId, QString message);

    void flushSocket();

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
    void serverResponded(QString response);
    void nicknameChanged(QString nickname);
};

#endif // CHATCLIENT_H
