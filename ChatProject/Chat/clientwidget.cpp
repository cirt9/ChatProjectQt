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
    portInput->setPlaceholderText("Port");
    portInput->setObjectName("ClientWidgetInput");
    clientLayout->addWidget(portInput);

    stateButton = new QPushButton("Connect");
    stateButton->setObjectName("ClientWidgetStateButton");
    stateButton->setMinimumWidth(100);
    connect(stateButton, SIGNAL(clicked(bool)), this, SLOT(changeState()));
    clientLayout->addWidget(stateButton);
}

void ClientWidget::changeState()
{
    if(isConnected)
    {
        isConnected = false;
        stateButton->setText("Connect");
        emit disconnectClicked();
    }
    else
    {
        isConnected = true;
        stateButton->setText("Disconnect");
        QString ip = ipInput->text();
        int port = portInput->text().toInt();
        emit connectClicked(ip, port);
    }
}
