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

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    ChatClient * chatClient;
    QLineEdit * messageLine;
    QTextEdit * messagesArea;

private slots:
    void sendClicked();
    void writeReceivedMsgToTextEdit(QString msg);

public:
    MainWindow(QWidget * parent = nullptr);
    ~MainWindow() {}
};

#endif // MAINWINDOW_H
