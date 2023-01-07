#include "form.h"
#include "ui_form.h"

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);

    setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint
                   |Qt::WindowStaysOnTopHint|Qt::WindowSystemMenuHint);

    users["hemingqu"] = "何名取";
    users["juejin"] = "掘金";
    users["2023"] = "2023";
}

Form::~Form()
{
    delete ui;
}

void Form::keySelectItem(bool flag)
{
    int row = ui->listWidget->currentRow();
    if(flag)
    {
        if(row + 1 >= ui->listWidget->count())
            ui->listWidget->setCurrentRow(0);
        else
            ui->listWidget->setCurrentRow(row + 1);
    }
    else
    {
        if(row - 1 < 0)
            ui->listWidget->setCurrentRow(ui->listWidget->count() - 1);
        else
            ui->listWidget->setCurrentRow(row - 1);
    }
}

void Form::setFilter(QString filter)
{
    ui->listWidget->clear();
    for (int i = 0; i < users.count(); ++i) {
        addItem(users.keys().at(i),users.values().at(i),filter);
    }
    if(ui->listWidget->count() == 0)
    {
        close();
        return;
    }

    ui->listWidget->setCurrentRow(0);
    this->setAttribute(Qt::WA_ShowWithoutActivating);
    ui->listWidget->setFocus();
}

QString Form::getSelectName()
{
    QListWidgetItem *item = ui->listWidget->currentItem();
    if(item == nullptr)
        return "";
    return item->text();
}

void Form::addItem(QString userId, QString name, QString filter)
{
    if(!userId.contains(filter) && !name.contains(filter))
        return;

    QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
    item->setFont(QFont("",14));
    item->setText(name);
    ui->listWidget->addItem(item);
}

