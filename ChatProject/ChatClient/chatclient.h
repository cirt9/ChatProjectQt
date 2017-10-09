#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <QObject>
#include <QTcpSocket>

class ChatClient : QObject
{
    Q_OBJECT

private:
    QTcpSocket * clientSocket;

public:
    explicit ChatClient(QObject * parent = nullptr);
    ~ChatClient() {}

public slots:
    void connect(QString ip, int portNumber);
};

#endif // CHATCLIENT_H
