#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDesktopWidget>
#include <chatwidget.h>
#include <QStackedWidget>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <mainmenuwidget.h>
#include <serverwidget.h>
#include <clientwidget.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QStackedWidget * uiContainer;
    ChatWidget * chat;

    void createUi();
    void createMenu();
    void createServerUi();
    void createClientUi();
    QGridLayout * createCenteredLayout(QLayout * layout);
    QGridLayout * createCenteredLayout(QWidget * widget);

    void createChat();
    void resetChat();

private slots:
    void displayServer();
    void displayClient();

public:
    MainWindow(QWidget * parent = 0);
    ~MainWindow() {}

public slots:
    void displayMenu();
};

#endif // MAINWINDOW_H
