#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    w = new Form();
    ui->textEdit->installEventFilter(this);

    AtMemberTextObject *atObj = new AtMemberTextObject;
    ui->textEdit->document()->documentLayout()->registerHandler(AtTextFormat,atObj);
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
            }
            else if(k->key() == Qt::Key_Down)
            {
                if(w->isVisible())
                {
                    w->keySelectItem(true);
                    return true;
                }
            }
            else if(k->key() == Qt::Key_Left)
            {
                if(w->isVisible())
                {
                    w->close();
                    return QWidget::eventFilter(watched,event);
                }
            }
            else if(k->key() == Qt::Key_Right)
            {
                if(w->isVisible())
                {
                    w->close();
                    return QWidget::eventFilter(watched,event);
                }
            }
            else if(k->key() == Qt::Key_Space)
            {
                if(w->isVisible())
                {
                    w->close();
                    return true;
                }
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
            }
            else if(k->key() == Qt::Key_Backspace)
            {
                if(w->isVisible())
                {
                    w->close();
                    return true;
                }
            }
        }
    }
    return QWidget::eventFilter(watched,event);
}

void MainWindow::on_textEdit_cursorPositionChanged()
{
    QTextCursor tc = ui->textEdit->textCursor();
    int selectionStart = tc.selectionStart();   //光标位置
    QString textBeforeCursor = getTextBeforeCursor();//获取光标前的文本
//    qDebug()<<textBeforeCursor;
//    QTextBlock tb = tc.block();
//    QString tx = tb.text();
    if(textBeforeCursor.isEmpty())
    {
        if(w->isVisible())
            w->close();
        return;
    }
    QRect rect = ui->textEdit->cursorRect();                     //获取光标位置
    QPoint point = ui->textEdit->mapToGlobal(rect.topLeft());    //转换为全局坐标
    if(w->isVisible())
    {
        QString filter = textBeforeCursor.mid(
                    textBeforeCursor.lastIndexOf("@")+1,
                    selectionStart-textBeforeCursor.lastIndexOf("@"));
        w->setFilter(filter);
        w->move(point.x(),point.y()-w->height());
    }
    else
    {
       if(textBeforeCursor.endsWith("@"))
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
//    QString textBeforeCursor = getTextBeforeCursor();
//    qDebug()<<textBeforeCursor;
    while(!getTextBeforeCursor().endsWith("@"))
        ui->textEdit->textCursor().deletePreviousChar();
    if(getTextBeforeCursor().endsWith("@"))
        ui->textEdit->textCursor().deletePreviousChar();
    else
        ;
//    ui->textEdit->textCursor().insertText(name);

    QTextCharFormat textcharFormat;
    textcharFormat.setVerticalAlignment(QTextCharFormat::AlignBottom);
    textcharFormat.setObjectType(AtTextFormat);
    textcharFormat.setProperty(AtData,QVariant(QString("@%1").arg(name)));
    textcharFormat.setProperty(AtFont,ui->textEdit->font());
//    ui->textEdit->mergeCurrentCharFormat(textcharFormat);

    QTextCursor cursor = ui->textEdit->textCursor();
//    cursor.movePosition(QTextCursor::End);
    cursor.insertText(QString(QChar::ObjectReplacementCharacter),textcharFormat);


//    qDebug()<<ui->textEdit->fontFamily();

//    cursor.insertText("关注我");

//    QString text;
//    QTextFrame::iterator it;                        //建立QTextFrame的迭代器
//    for (it = ui->textEdit->document()->rootFrame()->begin(); !(it.atEnd()); ++it) {
//        QTextBlock childBlock = it.currentBlock();  //获取当前文本块
//        if(childBlock.isValid())
//        {
//            QTextBlock::iterator itb;//文本片段的迭代，通过所在的容器的迭代器
//            for (itb = childBlock.begin(); !(itb.atEnd()); ++itb) {
//                QTextFragment currentFragment = itb.fragment();
//                if (currentFragment.isValid()) {
//                    if(currentFragment.charFormat().isCharFormat())
//                    {
//                        QTextCharFormat formt = currentFragment.charFormat();
//                        if(formt.objectType() == AtTextFormat)
//                            text += formt.property(AtData).toString();
//                        else
//                            text += currentFragment.text();
//                    }
//                }
//            }
//            if(!text.isEmpty())
//                text += '\n';
//        }
//    }

    //    ui->textEdit->append(text);
}

QString MainWindow::getTextBeforeCursor()
{
    QTextCursor tc = ui->textEdit->textCursor();
    int selectionStart = tc.selectionStart();   //光标位置
    QString textBeforeCursor = ui->textEdit->toPlainText().mid(0, selectionStart);//获取光标前的文本
    if(!textBeforeCursor.isEmpty())
        return textBeforeCursor;
    else
        return "";
}
