#include "chatwidget.h"

ChatWidget::ChatWidget(int chatMaxWidth, int barsHeight, QWidget * parent) : QWidget(parent)
{
    chatLayout = new QVBoxLayout();
    chatLayout->setSpacing(0);
    setLayout(chatLayout);

    setMaximumWidth(chatMaxWidth);

    QWidget * upperBar = createBar(barsHeight, "ChatWidgetUpperBar");
    chatLayout->addWidget(upperBar);

    QWidget * textArea = createTextArea();
    chatLayout->addWidget(textArea);

    QWidget * lowerBar = createBar(barsHeight, "ChatWidgetLowerBar");
    chatLayout->addWidget(lowerBar);
}

QWidget * ChatWidget::createBar(int height, QString objectName)
{
    QWidget * bar = new QWidget();
    bar->setObjectName(objectName);
    bar->setMaximumHeight(height);

    return bar;
}

QWidget * ChatWidget::createTextArea()
{
    QWidget * textArea = new QWidget();
    textArea->setObjectName("ChatWidgetTextArea");

    textAreaLayout = new QVBoxLayout();
    textArea->setLayout(textAreaLayout);

    return textArea;
}
