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

void MainWindow::displayMenu()
{

}

void MainWindow::createUi()
{
    createMenu();
}

void MainWindow::createMenu()
{
    QWidget * menuContainer = new QWidget();
    QVBoxLayout * menuLayout = new QVBoxLayout();
    menuLayout->setSpacing(10);

    menuLayout->addStretch(1);

    QLabel * title = new QLabel("Chat online");
    title->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    title->setObjectName("MainMenuTitleLabel");
    title->setAlignment(Qt::AlignCenter);
    menuLayout->addWidget(title);

    QLabel * author = new QLabel("Created by Bartłomiej Wójtowicz");
    author->setObjectName("MainMenuAuthorLabel");
    author->setAlignment(Qt::AlignHCenter);
    menuLayout->addWidget(author);

    menuLayout->addStretch(1);

    QPushButton * startServerButton = new QPushButton("Create New Server");
    startServerButton->setObjectName("MainMenuButton");
    menuLayout->addWidget(startServerButton);

    QPushButton * joinServerButton = new QPushButton("Join Existing Server");
    joinServerButton->setObjectName("MainMenuButton");
    menuLayout->addWidget(joinServerButton);

    QPushButton * quitButton = new QPushButton("Quit");
    quitButton->setObjectName("MainMenuButton");
    connect(quitButton, SIGNAL(clicked(bool)), this, SLOT(close()));
    menuLayout->addWidget(quitButton);

    menuLayout->addStretch(2);

    QGridLayout * centeredMenu = createCenteredLayout(menuLayout);
    menuContainer->setLayout(centeredMenu);
    uiContainer->addWidget(menuContainer);
}

void MainWindow::createServerUi()
{

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
