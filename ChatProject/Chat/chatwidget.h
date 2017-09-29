#ifndef CHATWIDGET_H
#define CHATWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QLineEdit>
#include <QTextEdit>

class ChatWidget : public QGroupBox
{
    Q_OBJECT
private:
    QVBoxLayout * chatLayout;
    QVBoxLayout * textAreaLayout;

    void createHeader(int height);
    void createFooter(int height);

    QWidget * createTextArea();

public:
    explicit ChatWidget(int maxWidth, int maxHeight, int barsHeight, QWidget * parent = 0);
};

#endif // CHATWIDGET_H
