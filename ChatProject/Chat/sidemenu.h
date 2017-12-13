#ifndef SIDEMENU_H
#define SIDEMENU_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QStackedWidget>
#include <QList>

class SideMenu : public QWidget
{
    Q_OBJECT
private:
    QHBoxLayout * layout;
    QStackedWidget * container;
    QVBoxLayout * buttonsLayout;

    QList<QPushButton *> buttons;

    int id;

public:
    SideMenu(QWidget * parent = nullptr);

    void addNewTab(QWidget * widget);

public slots:
    void testHide();
    void changeTab();
};

#endif // SIDEMENU_H
