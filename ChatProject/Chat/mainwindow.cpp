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
    QWidget * serverUiContainer = new QWidget();
    QGridLayout * serverLayout = new QGridLayout();
    serverLayout->setHorizontalSpacing(0);
    serverLayout->setAlignment(Qt::AlignTop);
    serverUiContainer->setLayout(serverLayout);

    QPushButton * backToMenuButton = new QPushButton("Menu");
    backToMenuButton->setObjectName("ServerUiLeftButton");
    connect(backToMenuButton, SIGNAL(clicked(bool)), this, SLOT(displayMenu()));
    serverLayout->addWidget(backToMenuButton, 0, 0);

    QLineEdit * portInput = new QLineEdit();
    portInput->setObjectName("ServerUiPortInput");
    portInput->setPlaceholderText("Port");
    serverLayout->addWidget(portInput, 0, 1);

    QPushButton * runButton = new QPushButton("Run");
    runButton->setObjectName("ServerUiRightButton");
    serverLayout->addWidget(runButton, 0, 2);

    uiContainer->addWidget(serverUiContainer);
}

void MainWindow::createClientUi()
{
    QWidget * clientUiContainer = new QWidget();
    QGridLayout * clientLayout = new QGridLayout();
    clientLayout->setAlignment(Qt::AlignTop);
    clientLayout->setSpacing(0);
    clientUiContainer->setLayout(clientLayout);

    QPushButton * backToMenuButton = new QPushButton("Menu");
    backToMenuButton->setObjectName("ClientUiLeftButton");
    connect(backToMenuButton, SIGNAL(clicked(bool)), this, SLOT(displayMenu()));
    clientLayout->addWidget(backToMenuButton, 0, 0);

    QLineEdit * portInput = new QLineEdit();
    portInput->setPlaceholderText("Port");
    portInput->setObjectName("ClientUiInput");
    clientLayout->addWidget(portInput, 0, 1);

    QLineEdit * ipInput = new QLineEdit();
    ipInput->setPlaceholderText("Ip Address");
    ipInput->setObjectName("ClientUiInput");
    clientLayout->addWidget(ipInput, 0, 2);

    QPushButton * connectButton = new QPushButton("Connect");
    connectButton->setObjectName("ClientUiRightButton");
    clientLayout->addWidget(connectButton, 0, 3);

    uiContainer->addWidget(clientUiContainer);
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
