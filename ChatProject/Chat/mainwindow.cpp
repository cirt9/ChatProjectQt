#include "mainwindow.h"

MainWindow::MainWindow(QWidget * parent) : QMainWindow(parent)
{
    MainWindow::setWindowTitle(QString("Chat"));
    resize(QDesktopWidget().availableGeometry(this).size() * 0.7);

    ChatWidget * chat = new ChatWidget(550, 350, 40, this);
    chat->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    //setCentralWidget(chat);

    chat->move(10, 10);
}
