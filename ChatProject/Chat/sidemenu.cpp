#include "sidemenu.h"
#include <QDebug>

SideMenu::SideMenu(QWidget * parent) : QWidget(parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    layout = new QHBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    setLayout(layout);

    //
    id = 0;
    //

    container = new QStackedWidget();
    container->setObjectName("SideMenuContainer");
    container->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    container->setFixedWidth(100);
    container->setStyleSheet("background: white");
    //container->hide();
    layout->addWidget(container);

    buttonsLayout = new QVBoxLayout();
    buttonsLayout->setSpacing(0);
    buttonsLayout->setContentsMargins(0, 0, 0, 0);
    layout->addLayout(buttonsLayout);
}

void SideMenu::addNewTab(QWidget * widget)
{
    QPushButton * button = new QPushButton();
    button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    button->setFixedWidth(30);
    button->setObjectName("SideMenuButton");
    button->setProperty("id", id);
    connect(button, SIGNAL(clicked(bool)), this, SLOT(testHide()));
    connect(button, SIGNAL(clicked(bool)), this, SLOT(changeTab()));

    id++;
    buttonsLayout->addWidget(button);
    buttons.append(button);

    container->addWidget(widget);
}

void SideMenu::changeTab()
{
    QPushButton * button = (QPushButton *)sender();
    int buttonId = button->property("id").toInt();

    qDebug() << buttonId;
    container->setCurrentIndex(buttonId);
}

void SideMenu::testHide()
{
    if(/*container->count() > 0 &&*/ container->isHidden())
        container->show();
    else
        container->hide();
}
