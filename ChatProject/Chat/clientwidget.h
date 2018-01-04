#ifndef CLIENTWIDGET_H
#define CLIENTWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QIntValidator>
#include <QMessageBox>
#include <QHostAddress>

class ClientWidget : public QWidget
{
    Q_OBJECT

private:
    QHBoxLayout * clientLayout;
    QLineEdit * ipInput;
    QLineEdit * portInput;
    QPushButton * stateButton;

    static const int MIN_PORT = 1024;
    static const int MAX_PORT = 65535;

    bool connected;

    void createInterface();

private slots:
    void connOrDisconnClicked();

public:
    ClientWidget(QWidget * parent = nullptr);
    ~ClientWidget() {}

    void changeState();
    bool isConnected() const;

signals:
    void backClicked();
    void connectClicked(const QString & ip, int port);
    void disconnectClicked();
};

#endif // CLIENTWIDGET_H
