#ifndef SENDMSGEDIT_H
#define SENDMSGEDIT_H

#include <QTextEdit>
#include <QKeyEvent>
#include "atlistwidget.h"

class SendMsgEdit : public QTextEdit
{
    Q_OBJECT
public:
    explicit SendMsgEdit(QWidget *parent = nullptr);

    void closeAtDialog();

protected:
    void keyPressEvent(QKeyEvent *e) override;
    void mousePressEvent(QMouseEvent *event) override;  //单击时关闭艾特列表
    void focusOutEvent(QFocusEvent *e) override;        //失去焦点时关闭艾特列表
    void resizeEvent(QResizeEvent *e) override;         //重绘时关闭艾特列表

private slots:
    void on_textEdit_cursorPositionChanged();

    void receiveName(QString name);

    QString getTextBeforeCursor();

private:
    AtListWidget *atList;
};

#endif // SENDMSGEDIT_H
