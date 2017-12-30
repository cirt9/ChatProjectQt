#include "sidemenu.h"

SideMenu::SideMenu(QWidget * parent) : QWidget(parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    defaultButtonSize = 50;
    defaultButtonsIconSize = 40;

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
    connect(sideButton, SIGNAL(clicked()), this, SLOT(hideTabs()));
}

void SideMenu::addNewTab(QWidget * tab)
{
    CheckBox * button = createTabButton(buttons.size());
    addButtonToLayoutAndList(button);

    tabs->addWidget(tab);
}

void SideMenu::addNewTab(QWidget * tab, const QIcon & buttonIcon)
{
    CheckBox * button = createTabButton(buttons.size());
    button->setIcon(buttonIcon);
    addButtonToLayoutAndList(button);

    tabs->addWidget(tab);
}

void SideMenu::addNewTab(QWidget * tab, const QString & text)
{
    CheckBox * button = createTabButton(buttons.size());
    button->setText(text);
    addButtonToLayoutAndList(button);

    tabs->addWidget(tab);
}

CheckBox * SideMenu::createTabButton(int id)
{
    CheckBox * button = new CheckBox();
    button->setFixedSize(defaultButtonSize, defaultButtonSize);
    button->setObjectName("SideMenuCheckBox");
    button->setProperty("id", id);
    button->setIconSize(QSize(defaultButtonsIconSize, defaultButtonsIconSize));
    connect(button, SIGNAL(clicked()), this, SLOT(changeTab()));

    return button;
}

void SideMenu::addButtonToLayoutAndList(CheckBox * button)
{
    buttonsLayout->addWidget(button);
    buttonsLayout->setAlignment(button, Qt::AlignTop);
    buttons.append(button);
}

void SideMenu::removeLastTab()
{
    QWidget * toRemoveTab = tabs->widget(tabs->count()-1);
    tabs->removeWidget(toRemoveTab);
    toRemoveTab->deleteLater();

    CheckBox * toRemoveButton = buttons.last();
    buttons.removeLast();

    if(toRemoveButton->isChecked())
    {
        setButtonChecked(0);
        setDisplayedTab(0);
    }
    toRemoveButton->deleteLater();
}

void SideMenu::changeTab()
{
    CheckBox * button = (CheckBox *)sender();
    int buttonId = button->getProperty("id").toInt();

    button->setChecked();

    setButtonChecked(buttonId);
    tabs->setCurrentIndex(buttonId);
}

bool SideMenu::setButtonChecked(int id)
{
    if(id < buttons.size())
    {
        setButtonsUnchecked();

        for(auto button : buttons)
        {
            int buttonId = button->getProperty("id").toInt();

            if(buttonId == id)
            {
                button->setChecked();
                return true;
            }
        }
    }
    return false;
}

void SideMenu::setButtonsUnchecked()
{
    for(auto button : buttons)
    {
        if(button->isChecked())
            button->setUnchecked();
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

bool SideMenu::insertTab(int index, QWidget * tab)
{
    if(index < 0 || index > buttons.size())
        return false;

    increaseIds(index);
    CheckBox * button = createTabButton(index);
    insertButtonToLayoutAndList(index, button);
    tabs->insertWidget(index, tab);
    return true;
}

void SideMenu::increaseIds(int startFrom)
{
    for(int i=startFrom; i<buttons.size(); i++)
    {
        int currentId = buttons[i]->getProperty("id").toInt();
        buttons[i]->setProperty("id", currentId+1);
    }
}

bool SideMenu::removeTab(int index)
{
    if(index < 0 || index >= buttons.size())
        return false;

    QWidget * toRemoveTab = tabs->widget(index);
    tabs->removeWidget(toRemoveTab);
    toRemoveTab->deleteLater();

    CheckBox * toRemoveButton = buttons[index];
    buttons.removeAt(index);

    if(toRemoveButton->isChecked())
    {
        setButtonChecked(0);
        setDisplayedTab(0);
    }
    toRemoveButton->deleteLater();

    decreaseIds(index);
    return true;
}

void SideMenu::decreaseIds(int finishOn)
{
    for(int i=buttons.size()-1; i>=finishOn; i--)
    {
        int currentId = buttons[i]->getProperty("id").toInt();
        buttons[i]->setProperty("id", currentId-1);
    }
}

void SideMenu::insertButtonToLayoutAndList(int index, CheckBox * button)
{
    buttonsLayout->insertWidget(index, button);
    buttonsLayout->setAlignment(button, Qt::AlignTop);
    buttons.insert(index, button);
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

void SideMenu::setButtonsIconSize(const QSize & size)
{
    for(auto button : buttons)
        button->setIconSize(size);
}

void SideMenu::setButtonsContentsMargins(int left, int top, int right, int bottom)
{
    buttonsLayout->setContentsMargins(left, top, right, bottom);
}

void SideMenu::setButtonsSpacing(int spacing)
{
    buttonsLayout->setSpacing(spacing);
}

void SideMenu::setDefaultButtonSize(int size)
{
    defaultButtonSize = size;
}

void SideMenu::setDefaultButtonsIconSize(int size)
{
    defaultButtonsIconSize = size;
}

int SideMenu::getDefaultButtonSize() const
{
    return defaultButtonSize;
}

int SideMenu::getDefaultButtonsIconSize() const
{
    return defaultButtonsIconSize;
}
