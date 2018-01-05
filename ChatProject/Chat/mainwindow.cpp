#include "mainwindow.h"

MainWindow::MainWindow(QWidget * parent) : QMainWindow(parent)
{
    MainWindow::setWindowTitle(QString("Chat"));
    resize(QDesktopWidget().availableGeometry(this).size() * 0.7);

    uiContainer = new QStackedWidget();
    setCentralWidget(uiContainer);

    serverWidget = nullptr;
    clientWidget = nullptr;
    chat = nullptr;
    server = nullptr;
    client = nullptr;

    initServer();
    initClient();
    createUi();
}

void MainWindow::initServer()
{
    if(!server)
    {
        server = new ChatServer();
        connect(server, SIGNAL(nameChanged(QString)), this, SLOT(displayInfo(QString)));
        connect(server, SIGNAL(nameCurrentlyUsed(QString)), this, SLOT(displayInfo(QString)));
    }
}

void MainWindow::initClient()
{
    if(!client)
    {
        client = new ChatClient();
        client->enableKeepAliveOption();
    }
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
    menu->addEffectForTitle(createShadow());
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
        serverWidget->setContentsMargins(11, 11, 11, 11);
        connect(serverWidget, SIGNAL(backClicked()), this, SLOT(closeServer()));
        connect(serverWidget, SIGNAL(backClicked()), this, SLOT(displayMenu()));
        connect(serverWidget, SIGNAL(runClicked(int)), this, SLOT(startServer(int)));
        connect(serverWidget, SIGNAL(closeClicked()), this, SLOT(closeServer()));

        QVBoxLayout * serverLayout = new QVBoxLayout();
        serverLayout->setContentsMargins(0, 0, 0, 0);
        serverLayout->addWidget(serverWidget);
        serverLayout->setAlignment(serverWidget, Qt::AlignTop);

        SideMenu * sideMenu = createSideMenu();
        serverLayout->addWidget(sideMenu);
        serverLayout->setAlignment(sideMenu, Qt::AlignLeft);

        UserProfileWidget * profile = createUserProfileWidget();
        profile->setNickname(server->getServerName());
        sideMenu->insertTab(0, profile, QIcon(":/icons/profile.png"));
        sideMenu->setDisplayedTab(0);
        connect(profile, SIGNAL(profileUpdated(QString)), this, SLOT(changeServerName(QString)));
        connect(server, &ChatServer::serverReseted, profile, [=]{profile->setNickname(ChatServer::DEFAULT_SERVER_NAME);});

        QWidget * serverWidgetContainer = new QWidget();
        serverWidgetContainer->setLayout(serverLayout);

        uiContainer->addWidget(serverWidgetContainer);
    }
}

void MainWindow::createClientUi()
{
    if(!clientWidget)
    {
        clientWidget = new ClientWidget();
        clientWidget->setContentsMargins(11, 11, 11, 11);
        connect(clientWidget, SIGNAL(backClicked()), this, SLOT(disconnectFromServer()));
        connect(clientWidget, SIGNAL(backClicked()), this, SLOT(displayMenu()));
        connect(clientWidget, SIGNAL(connectClicked(QString, int)),
                this, SLOT(connectToServer(QString, int)));
        connect(clientWidget, SIGNAL(disconnectClicked()), this, SLOT(disconnectFromServer()));

        QVBoxLayout * clientLayout = new QVBoxLayout();
        clientLayout->setContentsMargins(0, 0, 0, 0);
        clientLayout->addWidget(clientWidget);
        clientLayout->setAlignment(clientWidget, Qt::AlignTop);

        SideMenu * sideMenu = createSideMenu();
        clientLayout->addWidget(sideMenu);
        clientLayout->setAlignment(sideMenu, Qt::AlignLeft);

        UserProfileWidget * profile = createUserProfileWidget();
        sideMenu->insertTab(0, profile, QIcon(":/icons/profile.png"));
        sideMenu->setDisplayedTab(0);

        QWidget * clientWidgetContainer = new QWidget();
        clientWidgetContainer->setLayout(clientLayout);

        uiContainer->addWidget(clientWidgetContainer);
    }
}

SideMenu * MainWindow::createSideMenu()
{
    SideMenu * sideMenu = new SideMenu();
    sideMenu->setContentsMargins(0, 0, 0, 11);

    QLabel * placeHolder = new QLabel("Nothing here");
    placeHolder->setAlignment(Qt::AlignCenter);
    placeHolder->setStyleSheet("background: rgb(35, 69, 146); color: rgb(122, 138, 175); font-size: 45px; font-weight: bold;");

    sideMenu->addNewTab(placeHolder);
    return sideMenu;
}

void MainWindow::changeServerName(const QString & name)
{
    if(server)
    {
        server->setServerName(name);
        chat->setCurrentUserNickname(name);
    }
    else
        errorReaction("Server could not change its name.");
}

UserProfileWidget * MainWindow::createUserProfileWidget()
{
    UserProfileWidget * profile = new UserProfileWidget("Profile");
    profile->disableNicknameWhitespaces();
    profile->setObjectName("UserProfileWidget");
    return profile;
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
    if(server)
    {
        bool success = server->listen(QHostAddress::Any, quint16(port));

        if(success)
        {
            connect(server, SIGNAL(messageReceived(QString, QString)),
                    this, SLOT(writeReceivedMsgToChat(QString, QString)));
            connect(chat, SIGNAL(messageSent(QString)), this, SLOT(sendMsgFromServer(QString)));

            chat->setCurrentUserNickname(server->getServerName());
            chat->setVisible(true);
            if(!serverWidget->isRunning())
                serverWidget->changeState();

            QMessageBox::information(this, "Server", "Server is now running");
        }
        else
            QMessageBox::critical(this, "Server", "Server failed to start");
    }
}

void MainWindow::closeServer()
{
    if(server->isListening())
    {
        server->closeServer();
        disconnect(server, SIGNAL(messageReceived(QString, QString)),
                   this, SLOT(writeReceivedMsgToChat(QString, QString)));
        disconnect(chat, SIGNAL(messageSent(QString)), this, SLOT(sendMsgFromServer(QString)));

        resetChat();
        chat->setVisible(false);

        if(serverWidget->isRunning())
            serverWidget->changeState();

        QMessageBox::information(this, "Server", "Server was closed");
    }
}

void MainWindow::sendMsgFromServer(const QString & msg)
{
    if(server)
        server->spreadMessage(server->getServerName(), msg);
}

void MainWindow::connectToServer(const QString & ip, int port)
{
    if(client)
    {
        if(!client->isConnected())
        {
            bool success = client->connectToServer(ip, port);

            if(success)
            {
                connect(client, SIGNAL(messageReceived(QString, QString)),
                        this, SLOT(writeReceivedMsgToChat(QString, QString)));
                connect(chat, SIGNAL(messageSent(QString)), this, SLOT(sendMsgFromClient(QString)));
                connect(client, SIGNAL(errorOccurred(QString)), this, SLOT(errorReaction(QString)));
                connect(client, SIGNAL(unscheduledDisconnection()),
                        this, SLOT(emergencyDisconnectFromServer()));
                connect(client, SIGNAL(nicknameChanged(QString)), chat,
                        SLOT(setCurrentUserNickname(QString)));

                chat->setVisible(true);
                if(!clientWidget->isConnected())
                    clientWidget->changeState();

                QMessageBox::information(this, "Client", "Connected");
            }
            else
                QMessageBox::warning(this, "Client", "Couldn't connect");
        }
    }
}

void MainWindow::disconnectFromServer()
{
    if(client)
    {
        if(client->isConnected())
        {
            client->disconnectFromServer();
            cleanUpClient();

            resetChat();
            chat->setVisible(false);
            QMessageBox::information(this, "Client", "Disconnected");
        }
    }
}

void MainWindow::emergencyDisconnectFromServer()
{
    if(client)
    {
        if(client->isConnected())
        {
            client->disconnectFromServer();
            cleanUpClient();

            resetChat();
            chat->setVisible(false);
            errorReaction(client->getLastError());
        }
    }
}

void MainWindow::cleanUpClient()
{
    disconnect(client, SIGNAL(messageReceived(QString, QString)),
               this, SLOT(writeReceivedMsgToChat(QString, QString)));
    disconnect(chat, SIGNAL(messageSent(QString)), this, SLOT(sendMsgFromClient(QString)));
    disconnect(client, SIGNAL(errorOccurred(QString)), this, SLOT(errorReaction(QString)));
    disconnect(client, SIGNAL(unscheduledDisconnection()),
               this, SLOT(emergencyDisconnectFromServer()));
    disconnect(client, SIGNAL(nicknameChanged(QString)), chat,
            SLOT(setCurrentUserNickname(QString)));

    if(clientWidget->isConnected())
        clientWidget->changeState();
}

void MainWindow::sendMsgFromClient(const QString & msg)
{
    if(client)
    {
        if(client->isConnected())
            client->sendMessage(msg);
    }
}

void MainWindow::writeReceivedMsgToChat(const QString & nickname, const QString & msg)
{
    if(chat)
        chat->addMsg(nickname, msg);
}

void MainWindow::errorReaction(const QString & error)
{
    QMessageBox::critical(this, "Error", error);
}

void MainWindow::displayInfo(const QString & info)
{
    QMessageBox::information(this, "Information", info);
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

QGraphicsDropShadowEffect * MainWindow::createShadow()
{
    QGraphicsDropShadowEffect * shadow = new QGraphicsDropShadowEffect();
    shadow->setBlurRadius(20);
    shadow->setXOffset(4);
    shadow->setYOffset(4);
    shadow->setColor(Qt::black);

    return shadow;
}
