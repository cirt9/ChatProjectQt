#include "sidemenu.h"
#include <QDebug>

SideMenu::SideMenu(QWidget * parent) : QWidget(parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    layout = new QHBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    setLayout(layout);

    initializeButtonsContainer();
    initializeTabs();
    createSideButton();
}

void SideMenu::initializeButtonsContainer()
{
    buttonsContainer = new QWidget();

    buttonsLayout = new QVBoxLayout();
    buttonsLayout->setSpacing(0);
    buttonsLayout->setAlignment(Qt::AlignTop);
    buttonsLayout->setContentsMargins(0, 0, 0, 0);
    buttonsContainer->setLayout(buttonsLayout);
    layout->addWidget(buttonsContainer);
}

void SideMenu::initializeTabs()
{
    tabs = new QStackedWidget();
    tabs->setObjectName("SideMenuContainer");
    tabs->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    tabs->setFixedWidth(100);
    tabs->setStyleSheet("background: white");
    layout->addWidget(tabs);
}

void SideMenu::createSideButton()
{
    QPushButton * button = new QPushButton();
    button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    button->setFixedWidth(20);
    button->setObjectName("SideMenuButton");
    layout->addWidget(button);
    connect(button, SIGNAL(clicked(bool)), this, SLOT(hideTabs()));
}

void SideMenu::addNewTab(QWidget * widget)
{
    QToolButton * button = new QToolButton();
    button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    button->setProperty("id", getAvailableId());
    connect(button, SIGNAL(clicked(bool)), this, SLOT(changeTab()));

    buttonsLayout->addWidget(button);
    buttons.append(button);

    tabs->addWidget(widget);
}

int SideMenu::getAvailableId()
{
    for(int i=0; i<buttons.size()+1; i++)
    {
        bool available = true;

        for(auto button : buttons)
        {
            int id = button->property("id").toInt();
            if(id == i)
            {
                available = false;
                break;
            }
        }

        if(available)
            return i;
    }
    return 0;
}

void SideMenu::changeTab()
{
    QToolButton * button = (QToolButton *)sender();
    int buttonId = button->property("id").toInt();

    qDebug() << buttonId;
    tabs->setCurrentIndex(buttonId);
}

void SideMenu::hideTabs()
{
    if(/*container->count() > 0 &&*/ tabs->isHidden())
    {
        buttonsContainer->show();
        tabs->show();
    }
    else
    {
        buttonsContainer->hide();
        tabs->hide();
    }
}
