#include "serverwidget.h"

ServerWidget::ServerWidget(QWidget * parent) : QWidget(parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    isRunning = false;

    serverLayout = new QHBoxLayout();
    serverLayout->setSpacing(0);
    serverLayout->setContentsMargins(0, 0, 0, 0);
    setLayout(serverLayout);

    createInterface();
}

void ServerWidget::createInterface()
{
    QPushButton * backButton = new QPushButton("Menu");
    backButton->setMinimumWidth(80);
    backButton->setObjectName("ServerWidgetBackButton");
    connect(backButton, SIGNAL(clicked(bool)), this, SIGNAL(backClicked()));
    serverLayout->addWidget(backButton);

    portInput = new QLineEdit();
    portInput->setObjectName("ServerWidgetInput");
    portInput->setPlaceholderText("Port number");
    portInput->setValidator(new QIntValidator(MIN_PORT, MAX_PORT, this));
    serverLayout->addWidget(portInput);

    stateButton = new QPushButton("Run");
    stateButton->setMinimumWidth(80);
    connect(stateButton, SIGNAL(clicked(bool)), this, SLOT(runOrCloseClicked()));
    stateButton->setObjectName("ServerWidgetStateButton");
    serverLayout->addWidget(stateButton);
}

void ServerWidget::runOrCloseClicked()
{
    if(isRunning)
        emit closeClicked();

    else
    {
        int port = portInput->text().toInt();

        if(port < MIN_PORT || port > MAX_PORT)
            QMessageBox::information(this, "Wrong port selected", "Select port number between 1024-65535");
        else
            emit runClicked(port);
    }
}

void ServerWidget::changeState()
{
    if(isRunning)
    {
        isRunning = false;
        stateButton->setText("Run");
    }
    else
    {
        isRunning = true;
        stateButton->setText("Close");
    }
}
