#ifndef CLIENTWIDGET_H
#define CLIENTWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QIntValidator>

class ClientWidget : public QWidget
{
    Q_OBJECT

private:
    QHBoxLayout * clientLayout;
    QLineEdit * ipInput;
    QLineEdit * portInput;
    QPushButton * stateButton;

    bool isConnected;

    void createInterface();

private slots:
    void changeState();

public:
    ClientWidget(QWidget * parent = nullptr);

signals:
    void backClicked();
    void connectClicked(QString ip, int port);
    void disconnectClicked();
};

#endif // CLIENTWIDGET_H
