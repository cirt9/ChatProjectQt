#ifndef SERVERWIDGET_H
#define SERVERWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>

class ServerWidget : public QWidget
{
    Q_OBJECT

private:
    QHBoxLayout * serverLayout;
    QLineEdit * portInput;
    QPushButton * controlButton;

    bool isRunning;

private slots:
    void changeControlState();

public:
    ServerWidget(QWidget * parent = nullptr);

signals:
    void backClicked();
    void runClicked(int port);
    void closeClicked();
};

#endif // SERVERWIDGET_H
