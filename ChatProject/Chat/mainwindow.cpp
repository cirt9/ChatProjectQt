#include "mainwindow.h"
#include <QLabel>
#include <QTextEdit>

MainWindow::MainWindow(QWidget * parent) : QMainWindow(parent)
{
    MainWindow::setWindowTitle(QString("Chat"));
    resize(QDesktopWidget().availableGeometry(this).size() * 0.7);

    ChatWidget * chat = new ChatWidget(40, this);
    chat->setObjectName("ChatWidget");
    chat->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    chat->enableMoving();
    chat->disableOffTheScreenMoving();
    chat->setFixedSize(550, 350);
    //setCentralWidget(chat);

    chat->move(10, 10);
}
