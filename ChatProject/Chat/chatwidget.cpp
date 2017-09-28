#include "chatwidget.h"

ChatWidget::ChatWidget(int maxWidth, int maxHeight, int barsHeight, QWidget * parent) : QGroupBox(parent)
{
    setFixedWidth(maxWidth);     //change to maximum in final version
    setFixedHeight(maxHeight);   // change to maximum in final version
    setObjectName("ChatWidget");

    chatLayout = new QVBoxLayout();
    chatLayout->setSpacing(0);
    chatLayout->setContentsMargins(0, 0, 0, 0);
    setLayout(chatLayout);

    createHeader(barsHeight);

    QWidget * textArea = createTextArea();
    chatLayout->addWidget(textArea);

    createFooter(barsHeight);
}

void ChatWidget::createHeader(int height)
{
    QWidget * headerBar = new QWidget();
    headerBar->setObjectName("ChatWidgetHeaderBar");
    headerBar->setFixedHeight(height);
    chatLayout->addWidget(headerBar);
}

void ChatWidget::createFooter(int height)
{
    QLineEdit * textInputBar = new QLineEdit();
    textInputBar->setObjectName("ChatWidgetTextInputBar");
    textInputBar->setFixedHeight(height);
    chatLayout->addWidget(textInputBar);
    textInputBar->setPlaceholderText("Send message");
}

QWidget * ChatWidget::createTextArea()
{
    QWidget * textArea = new QWidget();
    textArea->setObjectName("ChatWidgetTextArea");

    textAreaLayout = new QVBoxLayout();
    textAreaLayout->setContentsMargins(0, 11, 0, 11);
    textArea->setLayout(textAreaLayout);

    return textArea;
}
