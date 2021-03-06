#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDesktopWidget>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QPushButton>
#include <chatclient.h>
#include <QTextEdit>
#include <QMessageBox>

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    ChatClient * chatClient;
    QLineEdit * inputLine;
    QTextEdit * messagesArea;

private slots:
    void sendMessage();
    void writeReceivedMsg(const QString & nickname, const  QString & msg);

public:
    MainWindow(QWidget * parent = nullptr);
    ~MainWindow() {}

public slots:
    void errorReaction(const QString & error);
};

#endif // MAINWINDOW_H
