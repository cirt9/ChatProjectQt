#include "mainwindow.h"

MainWindow::MainWindow(QWidget * parent) : QMainWindow(parent)
{
    resize(QDesktopWidget().availableGeometry(this).size() * 0.7);

    chatClient = new ChatClient(this);
    connect(chatClient, SIGNAL(messageReceived(QString, QString)), this, SLOT(writeReceivedMsg(QString, QString)));
    connect(chatClient, SIGNAL(errorOccurred(QString)), this, SLOT(errorReaction(QString)));

    QWidget * container = new QWidget();
    setCentralWidget(container);

    QGridLayout * layout = new QGridLayout();
    layout->setAlignment(Qt::AlignTop);
    container->setLayout(layout);

    QLabel * address = new QLabel("IP address: ");
    layout->addWidget(address, 0, 0, 1, 1);

    QLineEdit * addressLine = new QLineEdit();
    layout->addWidget(addressLine, 0, 1, 1, 2);

    QLabel * port = new QLabel("Port: ");
    layout->addWidget(port, 1, 0, 1, 1);

    QLineEdit * portLine = new QLineEdit();
    layout->addWidget(portLine, 1, 1, 1, 2);

    QPushButton * connectButton = new QPushButton("Connect");
    layout->addWidget(connectButton, 2, 0, 1, 3);
    connect(connectButton, &QPushButton::clicked, chatClient,
            [=]{chatClient->connectToServer(addressLine->text(), portLine->text().toInt()); } );

    messagesArea = new QTextEdit();
    layout->addWidget(messagesArea, 3, 0, 1, 3);

    QLabel * message = new QLabel("Message: ");
    layout->addWidget(message, 4, 0);

    inputLine = new QLineEdit();
    layout->addWidget(inputLine, 4, 1);

    QPushButton * sendButton = new QPushButton("Send message");
    layout->addWidget(sendButton, 4, 2);
    connect(sendButton, SIGNAL(clicked()), this, SLOT(sendMessage()));
}

void MainWindow::sendMessage()
{
    QString message = inputLine->text();
    chatClient->sendMessage(message);
    messagesArea->append(message);
}

void MainWindow::writeReceivedMsg(QString nickname, QString msg)
{
    messagesArea->append(nickname + ": " + msg);
}

void MainWindow::errorReaction(QString error)
{
    QMessageBox::critical(this, QString("Error"), error);
}
