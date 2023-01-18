#include "sendmsgedit.h"
#include "atmembertextobject.h"


SendMsgEdit::SendMsgEdit(QWidget *parent) :
    QTextEdit(parent)
{
    connect(this,SIGNAL(cursorPositionChanged()),
            this,SLOT(on_textEdit_cursorPositionChanged()));

    atList = new AtListWidget(this);
    atList->setHidden(true);
    connect(atList,&AtListWidget::itemClicked,
            [=](QListWidgetItem *item){receiveName(item->text());});

    AtMemberTextObject *atObj = new AtMemberTextObject;
    document()->documentLayout()->registerHandler(AtTextFormat,atObj);
}

void SendMsgEdit::closeAtDialog()
{
    if(atList->isVisible())
    {
        atList->setHidden(true);
        return;
    }
}

void SendMsgEdit::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Up)
    {
        if(atList->isVisible())
        {
            atList->keySelectItem(false);
            return;
        }
    }
    else if(e->key() == Qt::Key_Down)
    {
        if(atList->isVisible())
        {
            atList->keySelectItem(true);
            return;
        }
    }
    else if(e->key() == Qt::Key_Space)
    {
        if(atList->isVisible())
        {
            atList->setHidden(true);
            return;
        }
    }
    else if(e->key() == Qt::Key_Return || e->key() == Qt::Key_Enter)
    {
        if(atList->isVisible())
        {
            QString name = atList->getSelectName();
            receiveName(name);
            atList->setHidden(true);
            return;
        }
    }
    else if(e->key() == Qt::Key_Backspace)
    {
        if(atList->isVisible())
        {
            atList->setHidden(true);
            return;
        }
    }
    QTextEdit::keyPressEvent(e);
}

void SendMsgEdit::mousePressEvent(QMouseEvent *event)
{
    //如果鼠标左键按下
    if (event->button() == Qt::LeftButton) {
        if(!atList->isHidden())
        {
            atList->setHidden(true);
            return;
        }
    }
//	// 如果是鼠标右键按下
//	else if(event->button() == Qt::RightButton)
//	{
//	   //···
//	}
    QTextEdit::mousePressEvent(event);
}

void SendMsgEdit::focusOutEvent(QFocusEvent *e)
{
    if(!atList->isHidden())
    {
        atList->setHidden(true);
        return;
    }
    QTextEdit::focusOutEvent(e);
}

void SendMsgEdit::resizeEvent(QResizeEvent *e)
{
    if(!atList->isHidden())
    {
        atList->setHidden(true);
        return;
    }
    QTextEdit::resizeEvent(e);
}

void SendMsgEdit::on_textEdit_cursorPositionChanged()
{
    QTextCursor tc = textCursor();
    int selectionStart = tc.selectionStart();   //光标位置
    QString textBeforeCursor = getTextBeforeCursor();//获取光标前的文本
    if(textBeforeCursor.isEmpty())
    {
        if(atList->isVisible())
            atList->setHidden(true);
        return;
    }
    QRect rect = cursorRect();                     //获取光标位置
    QPoint point = mapToGlobal(rect.topLeft());    //转换为全局坐标
    if(atList->isVisible())
    {
        QString filter = textBeforeCursor.mid(
                    textBeforeCursor.lastIndexOf("@")+1,
                    selectionStart-textBeforeCursor.lastIndexOf("@"));
        atList->setFilter(filter);
        atList->move(point.x(),point.y()-atList->height());
    }
    else
    {
       if(textBeforeCursor.endsWith("@"))
       {
           atList->setFilter("");
           atList->setFocus();

           atList->setHidden(false);
           atList->move(point.x(),point.y()-atList->height());

           activateWindow();
           setFocus();
       }
    }
}

void SendMsgEdit::receiveName(QString name)
{
    while(!getTextBeforeCursor().endsWith("@"))
        textCursor().deletePreviousChar();
    if(getTextBeforeCursor().endsWith("@"))
        textCursor().deletePreviousChar();
    else
        ;

    QTextCharFormat textcharFormat;
    textcharFormat.setVerticalAlignment(QTextCharFormat::AlignBottom);
    textcharFormat.setObjectType(AtTextFormat);
    textcharFormat.setProperty(AtData,QVariant(QString("@%1").arg(name)));
    textcharFormat.setProperty(AtFont,font());

    QTextCursor cursor = textCursor();
    cursor.insertText(QString(QChar::ObjectReplacementCharacter),textcharFormat);
}

QString SendMsgEdit::getTextBeforeCursor()
{
    QTextCursor tc = textCursor();
    int selectionStart = tc.selectionStart();   //光标位置
    QString textBeforeCursor = toPlainText().mid(0, selectionStart);//获取光标前的文本
    if(!textBeforeCursor.isEmpty())
        return textBeforeCursor;
    else
        return "";
}
