#ifndef CHATWIDGET_H
#define CHATWIDGET_H

#include <QVBoxLayout>
#include <QGroupBox>
#include <QLineEdit>
#include <QTextEdit>
#include <QFont>

class ChatWidget : public QGroupBox
{
    Q_OBJECT
private:
    QVBoxLayout * chatLayout;
    QVBoxLayout * messagesLayout;
    size_t maxMsgWidth;

    void createHeader(int height);
    void createMessagesLayout();
    void createFooter(int height);

    size_t computeMessageHeight(QFont & messageFont, QString message);

public:
    explicit ChatWidget(int maxWidth, int maxHeight, int barsHeight, QWidget * parent = 0);

    void addMsg(QString nickname, QString message);
};

#endif // CHATWIDGET_H
