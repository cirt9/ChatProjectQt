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

    void setButtonsUnchecked();

private slots:
    void changeTab();

public:
    SideMenu(QWidget * parent = nullptr);
    ~SideMenu() {}

    void addNewTab(QWidget * widget, QString buttonObjectName);
    void removeLastTab();
    bool setButtonChecked(int id);
    bool setDisplayedTab(int id);

    void setTabsWidth(int width);
    void setSideButtonWidth(int width);
    void setButtonsSize(int width, int height);
    void setButtonsContentsMargins(int left, int top, int right, int bottom);
    void setButtonsSpacing(int spacing);

public slots:
    void hideTabs();
};

#endif // SIDEMENU_H
