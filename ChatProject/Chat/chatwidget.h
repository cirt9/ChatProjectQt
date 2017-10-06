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

    void createHeader(int height);
    void createMessagesArea();
    void createFooter(int height);

    void scrollMaxToBottom();

    void mousePressEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent * event);

public:
    explicit ChatWidget(int maxWidth, int maxHeight, int barsHeight, QWidget * parent = 0);

    void addMsg(QString nickname, QString message);

    void enableMoving(bool enable = true);
    void disableOffTheScreenMoving(bool disable = true);

public slots:
    void messageSent();
};

#endif // CHATWIDGET_H
