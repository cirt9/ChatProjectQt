#ifndef SIDEMENU_H
#define SIDEMENU_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QStackedWidget>
#include <QList>
#include <QCheckBox>

class SideMenu : public QWidget
{
    Q_OBJECT
private:
    QHBoxLayout * layout;
    QStackedWidget * tabs;

    QVBoxLayout * buttonsLayout;
    QWidget * buttonsContainer;
    QList<QCheckBox *> buttons;
    QPushButton * sideButton;

    void initializeButtonsContainer();
    void initializeTabs();
    void createSideButton();

    void riseButtons();

private slots:
    void hideTabs();
    void changeTab();

public:
    SideMenu(QWidget * parent = nullptr);

    void addNewTab(QWidget * widget);
    void removeLastTab();
    bool setDownButton(int id);
    bool setDisplayedTab(int id);

    void setTabsWidth(int width);
    void setSideButtonWidth(int width);
    void setButtonsSize(int width, int height);
    void setButtonsContentsMargins(int left, int top, int right, int bottom);
    void setButtonsSpacing(int spacing);
};

#endif // SIDEMENU_H
