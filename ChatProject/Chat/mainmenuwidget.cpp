#include "mainmenuwidget.h"

MainMenuWidget::MainMenuWidget(QWidget * parent) : QWidget(parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    menuLayout = new QVBoxLayout();
    menuLayout->setAlignment(Qt::AlignTop);
    menuLayout->setSpacing(10);
    setLayout(menuLayout);

    menuLayout->addStretch(1);

    QLabel * title = new QLabel("Chat online");
    title->setObjectName("MainMenuTitleLabel");
    title->setAlignment(Qt::AlignCenter);
    menuLayout->addWidget(title);

    menuLayout->addStretch(1);
    menuLayout->addStretch(2);
}

void MainMenuWidget::addTextBelowTitle(QString text)
{
    QLabel * textBelowTitle = new QLabel(text);
    textBelowTitle->setObjectName("MainMenuBelowTitleLabel");
    textBelowTitle->setAlignment(Qt::AlignHCenter);
    menuLayout->insertWidget(2, textBelowTitle);
}

void MainMenuWidget::addButton(QString text)
{
    QPushButton * button = new QPushButton(text);
    button->setObjectName("MainMenuButton");
    buttons.push_back(button);
    menuLayout->insertWidget(menuLayout->count() - 1, button);
}

QPushButton * MainMenuWidget::getButton(size_t index) const
{
    return buttons[index];
}

