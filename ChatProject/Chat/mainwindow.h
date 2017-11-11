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
#include <../ChatClient/chatclient.h>
#include <QMessageBox>

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QStackedWidget * uiContainer;

    ChatWidget * chat;
    ServerWidget * serverWidget;
    ClientWidget * clientWidget;
    ChatServer * server;
    ChatClient * client;

    void createUi();
    void createMenu();
    void createServerUi();
    void createClientUi();
    QGridLayout * createCenteredLayout(QLayout * layout);
    QGridLayout * createCenteredLayout(QWidget * widget);

    void createChat();
    void resetChat();
    void cleanUpClient();

private slots:
    void displayServer();
    void startServer(int port);
    void closeServer();
    void sendMsgFromServer(QString msg);

    void displayClient();
    void connectToServer(QString ip, int port);
    void disconnectFromServer();
    void emergencyDisconnectFromServer();
    void sendMsgFromClient(QString msg);

    void writeReceivedMsgToChat(QString msg);

    void errorReaction(QString error);

public:
    MainWindow(QWidget * parent = 0);
    ~MainWindow() {}

public slots:
    void displayMenu();
};

#endif // MAINWINDOW_H
