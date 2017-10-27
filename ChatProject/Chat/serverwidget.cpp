#include "serverwidget.h"

ServerWidget::ServerWidget(QWidget * parent) : QWidget(parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    isRunning = false;

    serverLayout = new QHBoxLayout();
    serverLayout->setSpacing(0);
    setLayout(serverLayout);

    QPushButton * backButton = new QPushButton("Menu");
    backButton->setMinimumWidth(100);
    backButton->setObjectName("ServerWidgetBackButton");
    connect(backButton, SIGNAL(clicked(bool)), this, SIGNAL(backClicked()));
    serverLayout->addWidget(backButton);

    portInput = new QLineEdit();
    portInput->setObjectName("ServerWidgetPortInput");
    portInput->setPlaceholderText("Port");
    serverLayout->addWidget(portInput);

    controlButton = new QPushButton("Run");
    controlButton->setMinimumWidth(100);
    connect(controlButton, SIGNAL(clicked(bool)), this, SLOT(changeControlState()));
    controlButton->setObjectName("ServerWidgetControlButton");
    serverLayout->addWidget(controlButton);
}

void ServerWidget::changeControlState()
{
    if(isRunning)
    {
        isRunning = false;
        controlButton->setText("Run");
        emit closeClicked();
    }
    else
    {
        isRunning = true;
        controlButton->setText("Close");
        int port = portInput->text().toInt();
        emit runClicked(port);
    }
}
