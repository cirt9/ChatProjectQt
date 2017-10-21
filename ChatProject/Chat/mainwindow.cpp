#include "mainwindow.h"

MainWindow::MainWindow(QWidget * parent) : QMainWindow(parent)
{
    MainWindow::setWindowTitle(QString("Chat"));
    resize(QDesktopWidget().availableGeometry(this).size() * 0.7);

    uiContainer = new QStackedWidget();
    setCentralWidget(uiContainer);

    createMenu();

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

void MainWindow::createMenu()
{
    QWidget * menuContainer = new QWidget();
    QGridLayout * menuLayout = new QGridLayout();

    QSpacerItem * leftSpacer = new QSpacerItem(0, QSizePolicy::Expanding, QSizePolicy::Expanding);
    menuLayout->addItem(leftSpacer, 0, 0);
    QSpacerItem * rightSpacer = new QSpacerItem(0, QSizePolicy::Expanding, QSizePolicy::Expanding);
    menuLayout->addItem(rightSpacer, 0, 2);

    QLabel * title = new QLabel("Chat");
    title->setObjectName("MainMenuTitleLabel");
    title->setAlignment(Qt::AlignCenter);
    menuLayout->addWidget(title, 0, 1, Qt::AlignTop);

    QLabel * author = new QLabel("Created by Bartłomiej Wójtowicz");
    author->setObjectName("MainMenuAuthorLabel");
    author->setAlignment(Qt::AlignRight);
    menuLayout->addWidget(author, 1, 1, Qt::AlignTop);

    QPushButton * startServerButton = new QPushButton("Create new server");
    menuLayout->addWidget(startServerButton, 2, 1);

    QPushButton * joinServerButton = new QPushButton("Join existing server");
    menuLayout->addWidget(joinServerButton, 3, 1);

    QPushButton * quitButton = new QPushButton("Quit");
    menuLayout->addWidget(quitButton, 4, 1);

    menuContainer->setLayout(menuLayout);
    uiContainer->addWidget(menuContainer);
}
