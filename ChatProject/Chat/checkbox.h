#ifndef CHECKBOX_H
#define CHECKBOX_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVariant>

class CheckBox : protected QWidget
{
    Q_OBJECT

private:
    bool checked;

    QHBoxLayout * layout;
    QPushButton * uncheckedButton;
    QPushButton * checkedButton;

public:
    explicit CheckBox(QWidget * parent = nullptr);

    void setProperty(const char *name, const QVariant value);
    QVariant getProperty(const char *name);
    bool isChecked() const;

    void setIcon(const QIcon & icon);
    void setCheckedIcon(const QIcon & icon);
    void setIconSize(const QSize & size);
    void setUncheckedIcon(const QIcon & icon);
    void setUncheckedText(const QString & text);
    void setCheckedText(const QString & text);
    void setObjectName(const QString & objectName);
    void setFixedSize(int w, int h);
    void setFixedHeight(int h);
    void setFixedWidth(int w);
    void setMaximumSize(int w, int h);
    void setMaximumHeight(int h);
    void setMaximumWidth(int w);
    void setMinimumSize(int w, int h);
    void setMinimumHeight(int h);
    void setMinimumWidth(int w);
    void setSizePolicy(QSizePolicy policy);

public slots:
    void setChecked();
    void setUnchecked();
    void deleteLater();

signals:
    void toggled();
    void clicked();
};

#endif // CHECKBOX_H
