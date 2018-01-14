#include "userprofilewidget.h"

UserProfileWidget::UserProfileWidget(QString profileTitle, QWidget * parent) : QWidget(parent)
{
    QVBoxLayout * layout = new QVBoxLayout();
    setLayout(layout);

    QLabel * title = new QLabel(profileTitle);
    title->setObjectName("UserProfileWidgetTitle");
    title->setAlignment(Qt::AlignCenter);
    layout->addWidget(title);
    layout->setAlignment(title, Qt::AlignTop);

    layout->addStretch(1);

    QLabel * nicknameLabel = new QLabel("Nickname");
    nicknameLabel->setObjectName("UserProfileWidgetLabel");
    nicknameLabel->setAlignment(Qt::AlignLeft);
    layout->addWidget(nicknameLabel);
    layout->setAlignment(nicknameLabel, Qt::AlignTop);

    nicknameInput = new QLineEdit();
    nicknameInput->setObjectName("UserProfileWidgetInput");
    nicknameInput->setMaxLength(20);
    layout->addWidget(nicknameInput);
    layout->setAlignment(nicknameInput, Qt::AlignTop);

    layout->addStretch(5);

    button = new QPushButton("Update");
    button->setObjectName("UserProfileWidgetButton");
    layout->addWidget(button);
    layout->setAlignment(button, Qt::AlignBottom);
    connect(button, SIGNAL(clicked(bool)), this, SLOT(emitProfileUpdated()));
}

void UserProfileWidget::emitProfileUpdated()
{
    if(!nicknameInput->text().isEmpty())
        emit profileUpdated(nicknameInput->text());
}

void UserProfileWidget::setMaxNameLength(int length)
{
    nicknameInput->setMaxLength(length);
}

void UserProfileWidget::disableButton(bool disabled)
{
    button->setDisabled(disabled);
}

void UserProfileWidget::disableNicknameWhitespaces()
{
    QRegExp rx("^\\S+$");
    nicknameInput->setValidator(new QRegExpValidator(rx, this));
}

void UserProfileWidget::setNickname(const QString & nickname)
{
    nicknameInput->setText(nickname);
}

QString UserProfileWidget::getNickname() const
{
    return nicknameInput->text();
}

void UserProfileWidget::paintEvent(QPaintEvent *)
{
    QStyleOption option;
    option.init(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &option, &painter, this);
}
