#include "mainwindow.h"

MainWindow::MainWindow(QWidget * parent) : QMainWindow(parent)
{
    resize(QDesktopWidget().availableGeometry(this).size() * 0.7);
}
