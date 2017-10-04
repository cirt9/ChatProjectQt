#ifndef CHATWIDGET_H
#define CHATWIDGET_H

#include <QVBoxLayout>
#include <QGroupBox>
#include <QLineEdit>
#include <QTextEdit>
#include <QScrollBar>

class ChatWidget : public QGroupBox
{
    Q_OBJECT
private:
    QVBoxLayout * chatLayout;
    QTextEdit * messagesArea;
    QLineEdit * textInputBar;

    void createHeader(int height);
    void createMessagesArea();
    void createFooter(int height);

    void scrollMaxToBottom();

public:
    explicit ChatWidget(int maxWidth, int maxHeight, int barsHeight, QWidget * parent = 0);

    void addMsg(QString nickname, QString message);

public slots:
    void messageSent();
};

#endif // CHATWIDGET_H
