#ifndef MAINMENUWIDGET_H
#define MAINMENUWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QGraphicsEffect>

class MainMenuWidget : public QWidget
{
    Q_OBJECT

private:
    QVBoxLayout * menuLayout;
    QLabel * titleLabel;
    QList<QPushButton *> buttons;

public:
    MainMenuWidget(const QString & title, QWidget * parent = nullptr);
    ~MainMenuWidget() {}

    void addTextBelowTitle(const QString & text);
    void addEffectForTitle(QGraphicsEffect * effect);

    void addButton(const QString & text);
    void removeLastButton();
    QPushButton * getButton(size_t index) const;
};


#endif // MAINMENUWIDGET_H
