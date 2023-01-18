#ifndef ATLISTWIDGET_H
#define ATLISTWIDGET_H

#include <QListWidget>

class AtListWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit AtListWidget(QWidget *parent = nullptr);

    void keySelectItem(bool flag);  //上下按键选择item
    void setFilter(QString filter);
    QString getSelectName();

protected:


private:
    void addMemberItem(QString userId,QString name,QString filter);

signals:
    void insertName(QString name);

private:
    QMap<QString,QString> users;
};

#endif // ATLISTWIDGET_H
