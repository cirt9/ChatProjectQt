#include "mainwindow.h"

MainWindow::MainWindow(QWidget * parent) : QMainWindow(parent)
{
    resize(QDesktopWidget().availableGeometry(this).size() * 0.7);

    chatServer = new ChatServer(this);

    QWidget * container = new QWidget();
    setCentralWidget(container);

    QGridLayout * layout = new QGridLayout();
    layout->setAlignment(Qt::AlignTop);
    container->setLayout(layout);

    QLabel * port = new QLabel("Port: ");
    layout->addWidget(port, 0, 0);

    portLine = new QLineEdit();
    layout->addWidget(portLine, 0, 1, 1, 2);

    QPushButton * startButton = new QPushButton("Start");
    layout->addWidget(startButton, 1, 0, 1, 3);
    connect(startButton, SIGNAL(clicked()), this, SLOT(startServer()));

    messagesArea = new QTextEdit();
    layout->addWidget(messagesArea, 2, 0, 1, 3);

    QLabel * message = new QLabel("Message: ");
    layout->addWidget(message, 3, 0);

    inputLine = new QLineEdit();
    layout->addWidget(inputLine, 3, 1);

    QPushButton * sendButton = new QPushButton("Send message");
    connect(sendButton, SIGNAL(clicked()), this, SLOT(sendMessage()));
    layout->addWidget(sendButton, 3, 2);
}

void MainWindow::startServer()
{
    bool success = chatServer->listen(QHostAddress::Any, quint16(portLine->text().toInt()));

    if(success)
    {
        qDebug() << "Server started";
        connect(chatServer, SIGNAL(messageReceived(QString)), this, SLOT(writeReceivedMsg(QString)));
    }
    else
        qDebug() << "Server failed to start";
}

void MainWindow::writeReceivedMsg(QString msg)
{
    messagesArea->append(msg);
}

void MainWindow::sendMessage()
{
    QString message = inputLine->text();
    chatServer->send(message);
    messagesArea->append(message);
}
