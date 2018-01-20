#include "mainwindow.h"
#include <QApplication>
#include <QFile>

int main(int argc, char * argv[])
{
    QApplication a(argc, argv);

    QFile file(":/style/style.css");
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        a.setStyleSheet(file.readAll());
        file.close();
    }

    MainWindow w;
    w.show();
    w.displayMenu();

    return a.exec();
}
