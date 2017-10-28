#include "mainwindow.h"

MainWindow::MainWindow(QWidget * parent) : QMainWindow(parent)
{
    MainWindow::setWindowTitle(QString("Chat"));
    resize(QDesktopWidget().availableGeometry(this).size() * 0.7);

    uiContainer = new QStackedWidget();
    setCentralWidget(uiContainer);

    createUi();

    /*ChatWidget * chat = new ChatWidget(40, this);
    chat->setObjectName("ChatWidget");
    chat->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    chat->enableMoving();
    chat->disableOffTheScreenMoving();
    chat->setFixedSize(550, 350);
    //setCentralWidget(chat);

    chat->move(10, 10);
    */
}

void MainWindow::createUi()
{
    createMenu();
    createServerUi();
    createClientUi();
}

void MainWindow::createMenu()
{
    MainMenuWidget * menu = new MainMenuWidget("Chat Online");
    menu->addTextBelowTitle("Created by Bartłomiej Wójtowicz");
    menu->addButton("Create New Server");
    connect(menu->getButton(0), SIGNAL(clicked(bool)), this, SLOT(displayServer()));
    menu->addButton("Join Existing Server");
    connect(menu->getButton(1), SIGNAL(clicked(bool)), this, SLOT(displayClient()));
    menu->addButton("Quit");
    connect(menu->getButton(2), SIGNAL(clicked(bool)), this, SLOT(close()));

    QGridLayout * centeredMenu = createCenteredLayout(menu);

    QWidget * menuContainer = new QWidget();
    menuContainer->setLayout(centeredMenu);
    uiContainer->addWidget(menuContainer);
}

void MainWindow::createServerUi()
{
    ServerWidget * serverWidget = new ServerWidget();
    connect(serverWidget, SIGNAL(backClicked()), this, SLOT(displayMenu()));

    QVBoxLayout * serverLayout = new QVBoxLayout();
    serverLayout->addWidget(serverWidget);
    serverLayout->setAlignment(serverWidget, Qt::AlignTop);

    QWidget * serverWidgetContainer = new QWidget();
    serverWidgetContainer->setLayout(serverLayout);

    uiContainer->addWidget(serverWidgetContainer);
}

void MainWindow::createClientUi()
{
    ClientWidget * clientWidget = new ClientWidget();
    connect(clientWidget, SIGNAL(backClicked()), this, SLOT(displayMenu()));

    QVBoxLayout * clientLayout = new QVBoxLayout();
    clientLayout->addWidget(clientWidget);
    clientLayout->setAlignment(clientWidget, Qt::AlignTop);

    QWidget * clientWidgetContainer = new QWidget();
    clientWidgetContainer->setLayout(clientLayout);

    uiContainer->addWidget(clientWidgetContainer);
}

void MainWindow::displayMenu()
{
    uiContainer->setCurrentIndex(0);
}

void MainWindow::displayServer()
{
    uiContainer->setCurrentIndex(1);
}

void MainWindow::displayClient()
{
    uiContainer->setCurrentIndex(2);
}

QGridLayout * MainWindow::createCenteredLayout(QLayout * layout)
{
    QGridLayout * centeredLayout = new QGridLayout();

    QSpacerItem * leftSpacer = new QSpacerItem(0, QSizePolicy::Expanding, QSizePolicy::Expanding);
    centeredLayout->addItem(leftSpacer, 0, 0);

    centeredLayout->addLayout(layout, 0, 1);

    QSpacerItem * rightSpacer = new QSpacerItem(0, QSizePolicy::Expanding, QSizePolicy::Expanding);
    centeredLayout->addItem(rightSpacer, 0, 2);

    return centeredLayout;
}

QGridLayout * MainWindow::createCenteredLayout(QWidget * widget)
{
    QGridLayout * centeredLayout = new QGridLayout();

    QSpacerItem * leftSpacer = new QSpacerItem(0, QSizePolicy::Expanding, QSizePolicy::Expanding);
    centeredLayout->addItem(leftSpacer, 0, 0);

    centeredLayout->addWidget(widget, 0, 1);

    QSpacerItem * rightSpacer = new QSpacerItem(0, QSizePolicy::Expanding, QSizePolicy::Expanding);
    centeredLayout->addItem(rightSpacer, 0, 2);

    return centeredLayout;
}
