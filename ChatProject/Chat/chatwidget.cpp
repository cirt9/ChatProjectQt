#include "chatwidget.h"

ChatWidget::ChatWidget(int chatMaxWidth, int barsHeight, QWidget * parent) : QWidget(parent)
{
    chatLayout = new QVBoxLayout();
    chatLayout->setSpacing(0);
    setLayout(chatLayout);

    setMaximumWidth(chatMaxWidth);

    QWidget * upperBar = createBar(barsHeight);
    chatLayout->addWidget(upperBar);

    QWidget * textArea = new QWidget();
    textArea->setStyleSheet("background: grey");
    chatLayout->addWidget(textArea);

    QWidget * lowerBar = createBar(barsHeight);
    chatLayout->addWidget(lowerBar);
}

QWidget * ChatWidget::createBar(int height)
{
    QWidget * bar = new QWidget();
    bar->setStyleSheet("background: black");
    bar->setMaximumHeight(height);

    return bar;
}
