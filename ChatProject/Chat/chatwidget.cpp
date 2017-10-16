#include "chatwidget.h"

ChatWidget::ChatWidget(int barsHeight, QWidget * parent) : QGroupBox(parent)
{
    movingEnabled = false;
    offTheScreenMovingDisabled = false;

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
    messagesArea->setTextInteractionFlags(Qt::TextSelectableByMouse);
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

    connect(textInputBar, SIGNAL(returnPressed()), this, SLOT(sendMessage()));
}

void ChatWidget::addMsg(QString nickname, QString message)
{
    QString msgText = "<b>[" + nickname + "]</b>: " + message;

    messagesArea->append(msgText);
}

void ChatWidget::sendMessage()
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

void ChatWidget::mousePressEvent(QMouseEvent * event)
{
    offset = event->pos();

    QGroupBox::mousePressEvent(event);
}

void ChatWidget::mouseMoveEvent(QMouseEvent * event)
{
    if(movingEnabled)
    {
        QPoint toMove = parentWidget()->mapFromGlobal(QCursor::pos() - offset);

        if(offTheScreenMovingDisabled)
        {
            int boundary = 20;

            if(toMove.x() < - boundary) return;
            if(toMove.y() < - boundary) return;
            if (toMove.x() > parentWidget()->width() - this->width() + boundary) return;
            if (toMove.y() > parentWidget()->height() - this->height() + boundary) return;
        }
        move(toMove);
    }

    QGroupBox::mouseMoveEvent(event);
}

void ChatWidget::enableMoving(bool enable)
{
    movingEnabled = enable;
}

void ChatWidget::disableOffTheScreenMoving(bool disable)
{
    offTheScreenMovingDisabled = disable;
}
