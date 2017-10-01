#include "chatwidget.h"

ChatWidget::ChatWidget(int maxWidth, int maxHeight, int barsHeight, QWidget * parent) : QGroupBox(parent)
{
    setFixedWidth(maxWidth);     //change to maximum in final version
    setFixedHeight(maxHeight);   // change to maximum in final version
    maxMsgWidth = maxWidth;

    chatLayout = new QVBoxLayout();
    chatLayout->setSpacing(0);
    chatLayout->setContentsMargins(0, 0, 0, 0);
    setLayout(chatLayout);

    createHeader(barsHeight);
    createMessagesLayout();
    createFooter(barsHeight);

    //
    addMsg(QString("Nickname1"), QString("Hello"));
    addMsg(QString("Nickname2"), QString("blablabla blJQWJEJJQWJIJMPQWJEQW RJ J QRWJQWJ RJQW R"));
}

void ChatWidget::createHeader(int height)
{
    QWidget * headerBar = new QWidget();
    headerBar->setObjectName("ChatWidgetHeaderBar");
    headerBar->setFixedHeight(height);
    chatLayout->addWidget(headerBar);
}

void ChatWidget::createMessagesLayout()
{
    messagesLayout = new QVBoxLayout();
    messagesLayout->setContentsMargins(0, 5, 0, 5);
    chatLayout->addLayout(messagesLayout);
    chatLayout->setAlignment(messagesLayout, Qt::AlignTop);
}

void ChatWidget::createFooter(int height)
{
    QLineEdit * textInputBar = new QLineEdit();
    textInputBar->setObjectName("ChatWidgetTextInputBar");
    textInputBar->setFixedHeight(height);
    textInputBar->setPlaceholderText("Send message");
    chatLayout->addWidget(textInputBar);
    chatLayout->setAlignment(textInputBar, Qt::AlignBottom);
}

void ChatWidget::addMsg(QString nickname, QString message)
{
    QString msgText = "<b>" + nickname + "</b>: " + message;

    QTextEdit * msg = new QTextEdit();
    msg->setReadOnly(true);
    msg->setTextInteractionFlags(Qt::TextSelectableByKeyboard | Qt::TextSelectableByMouse);
    msg->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    msg->setObjectName("ChatWidgetMessage");
    msg->setText(msgText);
    msg->ensurePolished();

    QFont msgFont = msg->document()->defaultFont();
    msg->setMaximumHeight(computeMessageHeight(msgFont, msgText));

    messagesLayout->addWidget(msg);
}

size_t ChatWidget::computeMessageHeight(QFont & messageFont, QString message)
{
    QFontMetrics fontMetrics = QFontMetrics(messageFont);
    size_t height = fontMetrics.boundingRect(QRect(0, 0, maxMsgWidth, 100), Qt::TextWordWrap, message).height() + 12;

    return height;
}
