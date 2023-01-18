#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QMap>
#include <QKeyEvent>
#include <QGraphicsDropShadowEffect>

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    ~Form();

    void keySelectItem(bool flag);

    void setFilter(QString filter);

    QString getSelectName();

private:
    void addItem(QString userId,QString name,QString filter);

private:
    Ui::Form *ui;

    QMap<QString,QString> users;
};

#endif // FORM_H
