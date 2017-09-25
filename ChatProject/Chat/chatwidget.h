#ifndef CHATWIDGET_H
#define CHATWIDGET_H

#include <QWidget>
#include <QVBoxLayout>

class ChatWidget : public QWidget
{
    Q_OBJECT
private:
    QVBoxLayout * chatLayout;

    QWidget * createBar(int height);

public:
    explicit ChatWidget(int chatMaxWidth, int barsHeight, QWidget * parent = 0);
};

#endif // CHATWIDGET_H
