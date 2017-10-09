#include "mainwindow.h"

MainWindow::MainWindow(QWidget * parent) : QMainWindow(parent)
{
    resize(QDesktopWidget().availableGeometry(this).size() * 0.7);

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

    layout->setRowStretch(3, 100);

    QLabel * message = new QLabel("Message: ");
    layout->addWidget(message, 4, 0);

    QLineEdit * messageLine = new QLineEdit();
    layout->addWidget(messageLine, 4, 1);

    QPushButton * sendButton = new QPushButton("Send message");
    layout->addWidget(sendButton, 4, 2);
}
