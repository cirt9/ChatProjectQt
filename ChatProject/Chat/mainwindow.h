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
#include <QGraphicsDropShadowEffect>
#include <sidemenu.h>
#include <userprofilewidget.h>

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

    void initServer();
    void initClient();

    void createUi();
    void createMenu();
    void createServerUi();
    void createClientUi();
    QGridLayout * createCenteredLayout(QLayout * layout);
    QGridLayout * createCenteredLayout(QWidget * widget);

    void createChat();
    void resetChat();
    void cleanUpClient();

    QGraphicsDropShadowEffect * createShadow();
    SideMenu * createSideMenu();
    UserProfileWidget * createUserProfileWidget();

private slots:
    void displayServer();
    void startServer(int port);
    void closeServer();
    void sendMsgFromServer(const QString & msg);

    void displayClient();
    void connectToServer(const QString & ip, int port);
    void disconnectFromServer();
    void emergencyDisconnectFromServer();
    void sendMsgFromClient(const QString & msg);

    void writeReceivedMsgToChat(const QString & nickname, const QString & msg);

    void changeServerName(const QString & name);
    void changeClientName(const QString & name);
    void clientNameCorrectlyChanged(const QString & name);
    void displayInfo(const QString & info);
    void errorReaction(const QString & error);

public:
    MainWindow(QWidget * parent = 0);
    ~MainWindow() {}

public slots:
    void displayMenu();
};

#endif // MAINWINDOW_H
