#include "mainwindow.h"

MainWindow::MainWindow(QWidget * parent) : QMainWindow(parent)
{
    MainWindow::setWindowTitle(QString("Chat"));
    resize(QDesktopWidget().availableGeometry(this).size() * 0.7);

    uiContainer = new QStackedWidget();
    setCentralWidget(uiContainer);

    serverWidget = nullptr;
    chat = nullptr;
    server = new ChatServer();

    createUi();
}

void MainWindow::createUi()
{
    createMenu();
    createServerUi();
    createClientUi();
    createChat();
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
    if(!serverWidget)
    {
        serverWidget = new ServerWidget();
        connect(serverWidget, SIGNAL(backClicked()), this, SLOT(cleanUpServer()));
        connect(serverWidget, SIGNAL(backClicked()), this, SLOT(displayMenu()));
        connect(serverWidget, SIGNAL(runClicked(int)), this, SLOT(startServer(int)));
        connect(serverWidget, SIGNAL(closeClicked()), this, SLOT(closeServer()));

        QVBoxLayout * serverLayout = new QVBoxLayout();
        serverLayout->addWidget(serverWidget);
        serverLayout->setAlignment(serverWidget, Qt::AlignTop);

        QWidget * serverWidgetContainer = new QWidget();
        serverWidgetContainer->setLayout(serverLayout);

        uiContainer->addWidget(serverWidgetContainer);
    }
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
    resetChat();
    chat->setVisible(true);
}

void MainWindow::createChat()
{
    if(!chat)
    {
        chat = new ChatWidget(40, this);
        chat->setObjectName("ChatWidget");
        chat->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        chat->enableMoving();
        chat->disableOffTheScreenMoving();
        chat->setFixedSize(550, 350);

        size_t x = this->rect().width()/2 - chat->rect().width()/2;
        size_t y = this->rect().height()/2 - chat->rect().height()/2;

        chat->move(x, y);
        chat->setVisible(false);
    }
}

void MainWindow::cleanUpServer()
{
    resetChat();
    closeServer();
}

void MainWindow::resetChat()
{
    if(chat)
    {
        size_t x = this->rect().width()/2 - chat->rect().width()/2;
        size_t y = this->rect().height()/2 - chat->rect().height()/2;

        chat->move(x, y);
        chat->clear();
    }
}

void MainWindow::startServer(int port)
{
    bool success = server->listen(QHostAddress::Any, quint16(port));

    if(success)
    {
        QMessageBox::information(this, "Server", "Server is now running");
        connect(server, SIGNAL(messageReceived(QString)), this, SLOT(writeReceivedMsgToChat(QString)));
        connect(chat, SIGNAL(messageSent(QString)), this, SLOT(sendMsgFromServer(QString)));

        chat->setVisible(true);

        if(serverWidget)
            serverWidget->changeState();
    }
    else
        QMessageBox::critical(this, "Server", "Server failed to start");
}

void MainWindow::closeServer()
{
    if(server->isListening())
    {
        server->close();
        disconnect(server, SIGNAL(messageReceived(QString)), this, SLOT(writeReceivedMsgToChat(QString)));
        disconnect(chat, SIGNAL(messageSent(QString)), this, SLOT(sendMsgFromServer(QString)));

        cleanUpServer();
        chat->setVisible(false);

        if(serverWidget)
            serverWidget->changeState();
    }
}

void MainWindow::writeReceivedMsgToChat(QString msg)
{
    if(chat)
        chat->addMsg("Test", msg);
}

void MainWindow::sendMsgFromServer(QString msg)
{
    server->send(msg);
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
