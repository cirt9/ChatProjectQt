#ifndef SIDEMENU_H
#define SIDEMENU_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QStackedWidget>

class SideMenu : public QWidget
{
    Q_OBJECT
private:
    QHBoxLayout * layout;
    QStackedWidget * container;
    QVBoxLayout * buttonsLayout;

public:
    SideMenu(QWidget * parent = nullptr);

    void addNewTab(QWidget * widget);

public slots:
    void testHide();
};

#endif // SIDEMENU_H
