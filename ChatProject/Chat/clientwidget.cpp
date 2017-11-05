#include "clientwidget.h"

ClientWidget::ClientWidget(QWidget * parent) : QWidget(parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    isConnected = false;

    clientLayout = new QHBoxLayout();
    clientLayout->setSpacing(0);
    clientLayout->setContentsMargins(0, 0, 0, 0);
    setLayout(clientLayout);

    createInterface();
}

void ClientWidget::createInterface()
{
    QPushButton * backButton = new QPushButton("Menu");
    backButton->setObjectName("ClientWidgetBackButton");
    backButton->setMinimumWidth(80);
    connect(backButton, SIGNAL(clicked(bool)), this, SIGNAL(backClicked()));
    clientLayout->addWidget(backButton);

    ipInput = new QLineEdit();
    ipInput->setPlaceholderText("Ip Address");
    ipInput->setObjectName("ClientWidgetInput");
    clientLayout->addWidget(ipInput);

    portInput = new QLineEdit();
    portInput->setPlaceholderText("Port number");
    portInput->setValidator(new QIntValidator(MIN_PORT, MAX_PORT, this));
    portInput->setObjectName("ClientWidgetInput");
    clientLayout->addWidget(portInput);

    stateButton = new QPushButton("Connect");
    stateButton->setObjectName("ClientWidgetStateButton");
    stateButton->setMinimumWidth(100);
    connect(stateButton, SIGNAL(clicked(bool)), this, SLOT(connOrDisconnClicked()));
    clientLayout->addWidget(stateButton);
}

void ClientWidget::connOrDisconnClicked()
{
    if(isConnected)
        emit disconnectClicked();

    else
    {
        QString ipString = ipInput->text();
        int port = portInput->text().toInt();
        QHostAddress ip;

        if(ip.setAddress(ipString))
        {
            if(port < MIN_PORT || port > MAX_PORT)
                QMessageBox::warning(this, "Wrong port selected",
                                         "Select port number between 1024-65535");
            else
                emit connectClicked(ipString, port);
        }
        else
            QMessageBox::warning(this, "Wrong ip address",
                                     "Please select a valid ip address");
    }
}

void ClientWidget::changeState()
{
    if(isConnected)
    {
        isConnected = false;
        stateButton->setText("Connect");
    }
    else
    {
        isConnected = true;
        stateButton->setText("Disconnect");
    }
}
