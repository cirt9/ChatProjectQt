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

    /*QTextEdit * t = new QTextEdit();
    t->setStyleSheet("background: black; color: white; font-size: 25px;");
    t->setMaximumSize(300, 300);
    t->setReadOnly(true);
    t->setText("Hello guys i will be testing this text wrapping widget HELLOWHYARENTYOUWRAPPINGTHISTEXT HELLOGUYSIMCURIOUSWHEREITWILLWRAPTHETEXT"
               "SADQWEQWRQWEQWRQWEQWRQWTQWRQWUEIWHUQWHRWIUOQWUHROWIHF");
    t->setTextInteractionFlags(Qt::TextSelectableByMouse | Qt::TextSelectableByKeyboard);
    t->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setCentralWidget(t);*/
}
