#ifndef SIDEMENU_H
#define SIDEMENU_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QStackedWidget>
#include <QList>
#include <QToolButton>

class SideMenu : public QWidget
{
    Q_OBJECT
private:
    QHBoxLayout * layout;
    QStackedWidget * tabs;

    QVBoxLayout * buttonsLayout;
    QWidget * buttonsContainer;
    QList<QToolButton *> buttons;

    void initializeButtonsContainer();
    void initializeTabs();
    void createSideButton();

    int getAvailableId();

private slots:
    void hideTabs();
    void changeTab();

public:
    SideMenu(QWidget * parent = nullptr);

    void addNewTab(QWidget * widget);
};

#endif // SIDEMENU_H
