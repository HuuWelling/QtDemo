#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextBlock>
#include <QTextCursor>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    w = new Form();
    ui->textEdit->installEventFilter(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    if(w->isVisible())
        w->close();
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type() == QEvent::KeyPress)   //键盘按下事件
    {
        if(watched == ui->textEdit)         //事件发送者为输入框
        {
            QKeyEvent *k = static_cast<QKeyEvent *>(event);
            if(k->key() == Qt::Key_Up)
            {
                if(w->isVisible())
                {
                    w->keySelectItem(false);
                    return true;
                }
                else
                    return QWidget::eventFilter(watched,event);
            }
            else if(k->key() == Qt::Key_Down)
            {
                if(w->isVisible())
                {
                    w->keySelectItem(true);
                    return true;
                }
                else
                    return QWidget::eventFilter(watched,event);
            }
            else if(k->key() == Qt::Key_Space)
            {
                if(w->isVisible())
                {
                    w->close();
                    return true;
                }
                else
                    return QWidget::eventFilter(watched,event);
            }
            else if(k->key() == Qt::Key_Return || k->key() == Qt::Key_Enter)
            {
                if(w->isVisible())
                {
                    QString name = w->getSelectName();
                    receiveName(name);
                    w->close();
                    return true;
                }
                else
                    return QWidget::eventFilter(watched,event);
            }
            else if(k->key() == Qt::Key_Backspace)
            {
                if(w->isVisible())
                {
                    w->close();
                    return true;
                }
                else
                    return QWidget::eventFilter(watched,event);
            }
            else
                return QWidget::eventFilter(watched,event);
        }
        else
            return QWidget::eventFilter(watched,event);
    }
    else
        return QWidget::eventFilter(watched,event);
}


void MainWindow::on_textEdit_cursorPositionChanged()
{
    QTextCursor tc = ui->textEdit->textCursor();
    QTextBlock tb = tc.block();
    QString tx = tb.text();
    if(tx.isEmpty())
    {
        if(w->isVisible())
            w->close();
        return;
    }
    QRect rect = ui->textEdit->cursorRect();                     //获取光标位置
    QPoint point = ui->textEdit->mapToGlobal(rect.topLeft());    //转换为全局坐标
    if(w->isVisible())
    {
        w->setFilter(tx.mid(tx.lastIndexOf("@") + 1));
        w->move(point.x(),point.y()-w->height());
    }
    else
    {
       if(tx.endsWith("@"))
       {
           w->setFilter("");
           w->setFocus();

           w->show();
           w->move(point.x(),point.y()-w->height());

           ui->textEdit->activateWindow();
           ui->textEdit->setFocus();
       }
    }
}

void MainWindow::receiveName(QString name)
{
    while(!ui->textEdit->textCursor().block().text().endsWith("@"))
        ui->textEdit->textCursor().deletePreviousChar();
    if(ui->textEdit->textCursor().block().text().endsWith("@"))
    ;
    else
        ui->textEdit->textCursor().insertText("@");
    ui->textEdit->textCursor().insertText(name);
}
