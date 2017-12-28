#include "checkbox.h"

CheckBox::CheckBox(QWidget * parent) : QWidget(parent)
{
    setContentsMargins(0, 0, 0, 0);
    checked = false;

    layout = new QHBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    setLayout(layout);

    uncheckedButton = new QPushButton();
    uncheckedButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    connect(uncheckedButton, SIGNAL(clicked(bool)), this, SLOT(setChecked()));
    connect(uncheckedButton, SIGNAL(clicked(bool)), this, SIGNAL(clicked()));
    layout->addWidget(uncheckedButton);

    checkedButton = new QPushButton();
    checkedButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    connect(checkedButton, SIGNAL(clicked(bool)), this, SLOT(setUnchecked()));
    connect(checkedButton, SIGNAL(clicked(bool)), this, SIGNAL(clicked()));
    layout->addWidget(checkedButton);

    setUnchecked();
}

void CheckBox::setChecked()
{
    checked = true;
    uncheckedButton->setVisible(false);
    checkedButton->setVisible(true);

    emit toggled();
}

void CheckBox::setUnchecked()
{
    checked = false;
    uncheckedButton->setVisible(true);
    checkedButton->setVisible(false);

    emit toggled();
}

void CheckBox::setProperty(const char * name, const QVariant value)
{
    QWidget::setProperty(name, value);
}

QVariant CheckBox::getProperty(const char * name)
{
    return QWidget::property(name);
}

bool CheckBox::isChecked() const
{
    return checked;
}

void CheckBox::setIcon(const QIcon & icon)
{
    checkedButton->setIcon(icon);
    uncheckedButton->setIcon(icon);
}

void CheckBox::setCheckedIcon(const QIcon & icon)
{
    checkedButton->setIcon(icon);
}

void CheckBox::setIconSize(const QSize & size)
{
    checkedButton->setIconSize(size);
    uncheckedButton->setIconSize(size);
}

void CheckBox::setUncheckedIcon(const QIcon & icon)
{
    uncheckedButton->setIcon(icon);
}

void CheckBox::setUncheckedText(const QString & text)
{
    checkedButton->setText(text);
}

void CheckBox::setCheckedText(const QString & text)
{
    uncheckedButton->setText(text);
}

void CheckBox::setObjectName(const QString & objectName)
{
    QWidget::setObjectName(objectName);
    uncheckedButton->setObjectName(objectName+QString("Unchecked"));
    checkedButton->setObjectName(objectName+QString("Checked"));
}

void CheckBox::deleteLater()
{
    QWidget::deleteLater();
}

void CheckBox::setFixedSize(int w, int h)
{
    QWidget::setFixedSize(w, h);
}

void CheckBox::setFixedHeight(int h)
{
    QWidget::setFixedHeight(h);
}

void CheckBox::setFixedWidth(int w)
{
    QWidget::setFixedWidth(w);
}

void CheckBox::setMaximumSize(int w, int h)
{
    QWidget::setMaximumSize(w, h);
}

void CheckBox::setMaximumHeight(int h)
{
    QWidget::setMaximumHeight(h);
}

void CheckBox::setMaximumWidth(int w)
{
    QWidget::setMaximumWidth(w);
}

void CheckBox::setMinimumSize(int w, int h)
{
    QWidget::setMinimumSize(w, h);
}

void CheckBox::setMinimumHeight(int h)
{
    QWidget::setMinimumHeight(h);
}

void CheckBox::setMinimumWidth(int w)
{
    QWidget::setMinimumWidth(w);
}

void CheckBox::setSizePolicy(QSizePolicy policy)
{
    QWidget::setSizePolicy(policy);
}
