#include "mainwindow.h"
#include <QLabel>
#include <QTextEdit>

MainWindow::MainWindow(QWidget * parent) : QMainWindow(parent)
{
    MainWindow::setWindowTitle(QString("Chat"));
    resize(QDesktopWidget().availableGeometry(this).size() * 0.7);

    ChatWidget * chat = new ChatWidget(550, 350, 40, this);
    chat->setObjectName("ChatWidget");
    chat->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    //setCentralWidget(chat);

    chat->move(10, 10);
}
