#ifndef CHATWIDGET_H
#define CHATWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QGroupBox>

class ChatWidget : public QWidget
{
    Q_OBJECT
private:
    QVBoxLayout * chatLayout;
    QVBoxLayout * textAreaLayout;

    QWidget * createBar(int height, QString objectName);
    QWidget * createTextArea();

public:
    explicit ChatWidget(int chatMaxWidth, int barsHeight, QWidget * parent = 0);
};

#endif // CHATWIDGET_H
