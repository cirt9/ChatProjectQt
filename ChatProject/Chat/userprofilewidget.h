#ifndef USERPROFILEWIDGET_H
#define USERPROFILEWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QStyleOption>
#include <QPainter>

class UserProfileWidget : public QWidget
{
    Q_OBJECT

private:
    QVBoxLayout * layout;

    void paintEvent(QPaintEvent *);

public:
    UserProfileWidget(QWidget * parent = nullptr);
    ~UserProfileWidget(){}
};

#endif // USERPROFILEWIDGET_H
