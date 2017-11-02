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
#include <../ChatServer/chatserver.h>
#include <QMessageBox>

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QStackedWidget * uiContainer;

    ChatWidget * chat;
    ServerWidget * serverWidget;
    ChatServer * server;

    void createUi();
    void createMenu();
    void createServerUi();
    void createClientUi();
    QGridLayout * createCenteredLayout(QLayout * layout);
    QGridLayout * createCenteredLayout(QWidget * widget);

    void createChat();
    void resetChat();

private slots:
    void displayClient();

    void displayServer();
    void startServer(int port);
    void closeServer();
    void sendMsgFromServer(QString msg);
    void cleanUpServer();

    void writeReceivedMsgToChat(QString msg);

public:
    MainWindow(QWidget * parent = 0);
    ~MainWindow() {}

public slots:
    void displayMenu();
};

#endif // MAINWINDOW_H
