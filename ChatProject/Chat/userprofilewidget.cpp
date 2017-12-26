#include "userprofilewidget.h"

UserProfileWidget::UserProfileWidget(QWidget * parent) : QWidget(parent)
{
    QVBoxLayout * layout = new QVBoxLayout();
    setLayout(layout);

    QLabel * title = new QLabel("Profile");
    title->setObjectName("UserProfileWidgetTitle");
    title->setAlignment(Qt::AlignCenter);
    layout->addWidget(title);
    layout->setAlignment(title, Qt::AlignTop);

    layout->addStretch(1);

    QLabel * nicknameLabel = new QLabel("Nickname");
    nicknameLabel->setObjectName("UserProfileWidgetNicknameLabel");
    nicknameLabel->setAlignment(Qt::AlignLeft);
    layout->addWidget(nicknameLabel);
    layout->setAlignment(nicknameLabel, Qt::AlignTop);

    QLineEdit * nicknameInput = new QLineEdit();
    nicknameInput->setObjectName("UserProfileWidgetNicknameInput");
    layout->addWidget(nicknameInput);
    layout->setAlignment(nicknameInput, Qt::AlignTop);

    layout->addStretch(5);

    QPushButton * button = new QPushButton("Update");
    button->setObjectName("UserProfileWidgetButton");
    layout->addWidget(button);
    layout->setAlignment(button, Qt::AlignBottom);
}

void UserProfileWidget::paintEvent(QPaintEvent *)
{
    QStyleOption option;
    option.init(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &option, &painter, this);
}
