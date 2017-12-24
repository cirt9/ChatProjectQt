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
    sideButton = new QPushButton();
    sideButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    sideButton->setFixedWidth(20);
    sideButton->setObjectName("SideMenuButton");
    layout->addWidget(sideButton);
    connect(sideButton, SIGNAL(clicked(bool)), this, SLOT(hideTabs()));
}

void SideMenu::addNewTab(QWidget * widget)
{
    QCheckBox * button = new QCheckBox();
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

    QCheckBox * toRemoveButton = buttons.last();
    buttons.removeLast();

    if(toRemoveButton->isChecked())
    {
        setDownButton(0);
        setDisplayedTab(0);
    }
    toRemoveButton->deleteLater();
}

void SideMenu::changeTab()
{
    QCheckBox * button = (QCheckBox *)sender();
    int buttonId = button->property("id").toInt();

    button->setChecked(true);

    setDownButton(buttonId);
    tabs->setCurrentIndex(buttonId);
}

bool SideMenu::setDownButton(int id)
{
    if(id < buttons.size())
    {
        riseButtons();

        for(auto button : buttons)
        {
            int buttonId = button->property("id").toInt();

            if(buttonId == id)
            {
                button->setChecked(true);
                return true;
            }
        }
    }
    return false;
}

void SideMenu::riseButtons()
{
    for(auto button : buttons)
    {
        if(button->isChecked())
            button->setChecked(false);
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

bool SideMenu::setDisplayedTab(int id)
{
    if(id < tabs->count())
    {
        tabs->setCurrentIndex(id);
        return true;
    }
    return false;
}

void SideMenu::setTabsWidth(int width)
{
    tabs->setFixedWidth(width);
}

void SideMenu::setSideButtonWidth(int width)
{
    sideButton->setFixedWidth(width);
}

void SideMenu::setButtonsSize(int width, int height)
{
    for(auto button : buttons)
        button->setFixedSize(width, height);
}

void SideMenu::setButtonsContentsMargins(int left, int top, int right, int bottom)
{
    buttonsLayout->setContentsMargins(left, top, right, bottom);
}

void SideMenu::setButtonsSpacing(int spacing)
{
    buttonsLayout->setSpacing(spacing);
}
