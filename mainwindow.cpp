#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "atmembertextobject.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::moveEvent(QMoveEvent *e)
{
    ui->textEdit->closeAtDialog();
    QMainWindow::moveEvent(e);
}
