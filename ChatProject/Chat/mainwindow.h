#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDesktopWidget>
#include <chatwidget.h>
#include <QStackedWidget>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QStackedWidget * uiContainer;

    void createMenu();

public:
    MainWindow(QWidget * parent = 0);
    ~MainWindow() {}

public slots:
    //void displayMenu();
};

#endif // MAINWINDOW_H
