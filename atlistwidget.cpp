#include "atlistwidget.h"
#include <QGraphicsDropShadowEffect>
#include <QPainterPath>
#include <QPainter>

AtListWidget::AtListWidget(QWidget *parent) :
    QListWidget(parent)
{
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    users["hemingqu"] = "何名取";
    users["juejin"] = "掘金";
    users["2023"] = "2023";
//    //设置投影效果
//    QGraphicsDropShadowEffect *windowShadow;        //阴影效果
//    windowShadow = new QGraphicsDropShadowEffect(this);
//    windowShadow->setBlurRadius(30);
//    windowShadow->setColor(QColor(38, 78, 119, 127));
//    windowShadow->setOffset(0, 0);
//    setGraphicsEffect(windowShadow);
//    setContentsMargins(10,10,10,10);
}

void AtListWidget::keySelectItem(bool flag)
{
    int row = this->currentRow();
    if(flag)
    {
        if(row + 1 >= this->count())
            this->setCurrentRow(0);
        else
            this->setCurrentRow(row + 1);
    }
    else
    {
        if(row - 1 < 0)
            this->setCurrentRow(this->count() - 1);
        else
            this->setCurrentRow(row - 1);
    }
}

void AtListWidget::setFilter(QString filter)
{
    this->clear();
    for (int i = 0; i < users.count(); ++i) {
        addMemberItem(users.keys().at(i),users.values().at(i),filter);
    }
    if(this->count() == 0)
    {
        hide();
        return;
    }
    int height = count() < 5 ? 40*count()+7 : 200;
    this->resize(200,height);
    this->setCurrentRow(0);
    this->setAttribute(Qt::WA_ShowWithoutActivating);
    this->setFocus();
}

QString AtListWidget::getSelectName()
{
    QListWidgetItem *item = this->currentItem();
    if(item == nullptr)
        return "";
    return item->text();
}

void AtListWidget::addMemberItem(QString userId, QString name, QString filter)
{
    if(!userId.contains(filter) && !name.contains(filter))
        return;

    QListWidgetItem *item = new QListWidgetItem(this);
    item->setFont(QFont("",14));
    item->setText(name);
    item->setSizeHint(QSize(100,40));
    this->addItem(item);
}
