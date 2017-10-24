#ifndef MAINMENUWIDGET_H
#define MAINMENUWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>

class MainMenuWidget : public QWidget
{
    Q_OBJECT

private:
    QVBoxLayout * menuLayout;
    QList<QPushButton *> buttons;

public:
    MainMenuWidget(QWidget * parent = nullptr);

    void addTextBelowTitle(QString text);

    void addButton(QString text);
    QPushButton * getButton(size_t index) const;
};


#endif // MAINMENUWIDGET_H
