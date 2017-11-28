#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDesktopWidget>
#include <QLineEdit>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QGridLayout>
#include <chatserver.h>
#include <QMessageBox>

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    ChatServer * chatServer;
    QLineEdit * portLine;
    QTextEdit * messagesArea;
    QLineEdit * inputLine;

private slots:
    void startServer();
    void writeReceivedMsg(QString nickname, QString msg);
    void sendMessage();

public:
    MainWindow(QWidget * parent = nullptr);
    ~MainWindow() {}
};

#endif // MAINWINDOW_H
