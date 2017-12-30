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
    QLineEdit * nicknameInput;
    QPushButton * button;

    void paintEvent(QPaintEvent *);

private slots:
    void emitProfileUpdated();

public:
    UserProfileWidget(QString profileTitle, QWidget * parent = nullptr);
    ~UserProfileWidget(){}

    void setNickname(const QString & nickname);
    QString getNickname() const;
    void setMaxNameLength(int length);
    void disableButton(bool disabled);

signals:
    void profileUpdated(QString nickname);
};

#endif // USERPROFILEWIDGET_H
