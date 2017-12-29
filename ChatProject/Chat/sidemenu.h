#ifndef SIDEMENU_H
#define SIDEMENU_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QStackedWidget>
#include <QList>
#include <checkbox.h>

class SideMenu : public QWidget
{
    Q_OBJECT
private:
    QHBoxLayout * layout;
    QStackedWidget * tabs;

    QVBoxLayout * buttonsLayout;
    QWidget * buttonsContainer;
    QList<CheckBox *> buttons;
    QPushButton * sideButton;

    int defaultButtonSize;
    int defaultButtonsIconSize;

    void initializeButtonsContainer();
    void initializeTabs();
    void createSideButton();

    void setButtonsUnchecked();
    CheckBox * createTabButton();
    void addButtonToLayoutAndList(CheckBox * button);

private slots:
    void changeTab();

public:
    SideMenu(QWidget * parent = nullptr);
    ~SideMenu() {}

    void addNewTab(QWidget * widget);
    void addNewTab(QWidget * widget, const QIcon & buttonIcon);
    void addNewTab(QWidget * widget, const QString & text);
    void removeLastTab();
    bool setButtonChecked(int id);
    bool setDisplayedTab(int id);

    void setTabsWidth(int width);
    void setSideButtonWidth(int width);
    void setButtonsSize(int width, int height);
    void setButtonsIconSize(const QSize & size);
    void setButtonsContentsMargins(int left, int top, int right, int bottom);
    void setButtonsSpacing(int spacing);
    void setDefaultButtonSize(int size);
    void setDefaultButtonsIconSize(int size);

    int getDefaultButtonSize() const;
    int getDefaultButtonsIconSize() const;


public slots:
    void hideTabs();
};

#endif // SIDEMENU_H
