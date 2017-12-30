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
    CheckBox * createTabButton(int id);
    void addButtonToLayoutAndList(CheckBox * button);
    void insertButtonToLayoutAndList(int index, CheckBox * button);

    void increaseIds(int startFrom);
    void decreaseIds(int finishOn);

private slots:
    void changeTab();

public:
    SideMenu(QWidget * parent = nullptr);
    ~SideMenu() {}

    void addNewTab(QWidget * tab);
    void addNewTab(QWidget * tab, const QIcon & buttonIcon);
    void addNewTab(QWidget * tab, const QString & text);
    void removeLastTab();
    bool insertTab(int index, QWidget * tab);
    bool removeTab(int index);
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
