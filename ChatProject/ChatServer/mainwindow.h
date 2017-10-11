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

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    ChatServer * chatServer;
    QLineEdit * portLine;

private slots:
    void startServer();

public:
    MainWindow(QWidget * parent = nullptr);
    ~MainWindow() {}
};

#endif // MAINWINDOW_H
