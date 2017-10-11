#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDesktopWidget>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QPushButton>
#include <chatclient.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    ChatClient * chatClient;
    QLineEdit * messageLine;

private slots:
    void sendClicked();

public:
    MainWindow(QWidget * parent = nullptr);
    ~MainWindow() {}
};

#endif // MAINWINDOW_H
