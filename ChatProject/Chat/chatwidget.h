#ifndef CHATWIDGET_H
#define CHATWIDGET_H

#include <QVBoxLayout>
#include <QGroupBox>
#include <QLineEdit>
#include <QTextEdit>
#include <QScrollBar>
#include <QMouseEvent>
#include <QCursor>

class ChatWidget : public QGroupBox
{
    Q_OBJECT
private:
    QVBoxLayout * chatLayout;
    QTextEdit * messagesArea;
    QLineEdit * textInputBar;

    QPoint offset;
    bool movingEnabled;
    bool offTheScreenMovingDisabled;
    QString currentUserNickname;

    void createHeader(int height);
    void createMessagesArea();
    void createFooter(int height);

    void scrollMaxToBottom();

    void mousePressEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent * event);

private slots:
    void sendMessage();

public:
    explicit ChatWidget(int barsHeight, QWidget * parent = 0);
    ~ChatWidget() {}

    void addMsg(const QString & nickname, const QString & message);
    void clear();
    void reset();

    void enableMoving(bool enable = true);
    void disableOffTheScreenMoving(bool disable = true);

public slots:
    void setCurrentUserNickname(const QString & nickname);

signals:
    void messageSent(const QString & msg);
};

#endif // CHATWIDGET_H
