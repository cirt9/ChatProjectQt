#ifndef SERVERWIDGET_H
#define SERVERWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QIntValidator>
#include <QMessageBox>

class ServerWidget : public QWidget
{
    Q_OBJECT

private:
    QHBoxLayout * serverLayout;
    QLineEdit * portInput;
    QPushButton * stateButton;

    static const int MIN_PORT = 1024;
    static const int MAX_PORT = 65535;

    bool isRunning;

    void createInterface();

private slots:
    void runOrCloseClicked();

public:
    ServerWidget(QWidget * parent = nullptr);

    void changeState();

signals:
    void backClicked();
    void runClicked(int port);
    void closeClicked();
};

#endif // SERVERWIDGET_H
