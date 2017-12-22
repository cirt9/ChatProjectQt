#include "sidemenu.h"

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
    buttonsContainer->setObjectName("SideMenuButtonsContainer");

    buttonsLayout = new QVBoxLayout();
    buttonsLayout->setSpacing(10);
    buttonsLayout->setAlignment(Qt::AlignTop);
    buttonsLayout->setContentsMargins(4, 10, 4, 10);
    buttonsContainer->setLayout(buttonsLayout);
    buttonsContainer->hide();
    layout->addWidget(buttonsContainer);
}

void SideMenu::initializeTabs()
{
    tabs = new QStackedWidget();
    tabs->setObjectName("SideMenuContainer");
    tabs->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    tabs->setFixedWidth(350);
    tabs->hide();
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
    button->setFixedSize(60, 60);
    button->setObjectName("SideMenuToolButton");
    button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    button->setProperty("id", buttons.size());
    connect(button, SIGNAL(clicked(bool)), this, SLOT(changeTab()));

    buttonsLayout->addWidget(button);
    buttonsLayout->setAlignment(button, Qt::AlignTop);
    buttons.append(button);

    tabs->addWidget(widget);
}

void SideMenu::removeLastTab()
{
    QWidget * toRemoveTab = tabs->widget(tabs->count()-1);
    tabs->removeWidget(toRemoveTab);
    toRemoveTab->deleteLater();

    QToolButton * toRemoveButton = buttons.last();
    buttons.removeLast();

    if(toRemoveButton->isDown())
    {
        setDownButton(0);
        setTab(0);
    }
    toRemoveButton->deleteLater();
}

void SideMenu::changeTab()
{
    QToolButton * button = (QToolButton *)sender();
    int buttonId = button->property("id").toInt();

    setDownButton(buttonId);
    tabs->setCurrentIndex(buttonId);
}

void SideMenu::setDownButton(int id)
{
    riseButtons();

    for(auto button : buttons)
    {
        int buttonId = button->property("id").toInt();

        if(buttonId == id)
        {
            button->setDown(true);
            break;
        }
    }
}

void SideMenu::riseButtons()
{
    for(auto button : buttons)
    {
        if(button->isDown())
            button->setDown(false);
    }
}

void SideMenu::hideTabs()
{
    if(tabs->count() > 0 && tabs->isHidden())
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

void SideMenu::setTab(int id)
{
    tabs->setCurrentIndex(id);
}
