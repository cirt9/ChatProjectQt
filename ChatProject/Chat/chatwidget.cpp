#include "chatwidget.h"

ChatWidget::ChatWidget(int maxWidth, int maxHeight, int barsHeight, QWidget * parent) : QGroupBox(parent)
{
    setFixedWidth(maxWidth);     //change to maximum in final version
    setFixedHeight(maxHeight);   // change to maximum in final version

    chatLayout = new QVBoxLayout();
    chatLayout->setSpacing(0);
    chatLayout->setContentsMargins(0, 0, 0, 0);
    setLayout(chatLayout);

    createHeader(barsHeight);
    createMessagesArea();
    createFooter(barsHeight);
}

void ChatWidget::createHeader(int height)
{
    QWidget * headerBar = new QWidget();
    headerBar->setObjectName("ChatWidgetHeaderBar");
    headerBar->setFixedHeight(height);
    chatLayout->addWidget(headerBar);
}

void ChatWidget::createMessagesArea()
{
    messagesArea = new QTextEdit();
    messagesArea->setReadOnly(true);
    messagesArea->setTextInteractionFlags(Qt::TextSelectableByKeyboard | Qt::TextSelectableByMouse);
    messagesArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    messagesArea->setObjectName("ChatWidgetMessagesArea");
    messagesArea->setText("<b>[Server]</b>: Have a nice day!");

    QScrollBar * scrollBar = messagesArea->verticalScrollBar();
    scrollBar->setObjectName("ChatWidgetMessagesAreaScrollBar");

    chatLayout->addWidget(messagesArea);
}

void ChatWidget::createFooter(int height)
{
    textInputBar = new QLineEdit();
    textInputBar->setObjectName("ChatWidgetTextInputBar");
    textInputBar->setFixedHeight(height);
    textInputBar->setPlaceholderText("Send message");

    chatLayout->addWidget(textInputBar);
    chatLayout->setAlignment(textInputBar, Qt::AlignBottom);
    textInputBar->setFocus();

    connect(textInputBar, SIGNAL(returnPressed()), this, SLOT(messageSent()));
}

void ChatWidget::addMsg(QString nickname, QString message)
{
    QString msgText = "<b>[" + nickname + "]</b>: " + message;

    messagesArea->append(msgText);
}

void ChatWidget::messageSent()
{
    if(textInputBar->text().size() > 0)
    {
        addMsg("Nickname", textInputBar->text());
        scrollMaxToBottom();

        textInputBar->clear();
    }
}

void ChatWidget::scrollMaxToBottom()
{
    QScrollBar * scrollBar = messagesArea->verticalScrollBar();
    scrollBar->setValue(scrollBar->maximum());
}
