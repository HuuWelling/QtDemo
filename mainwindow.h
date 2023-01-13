#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextBlock>
#include <QTextCursor>
#include <QTextDocument>
#include <QAbstractTextDocumentLayout>
#include <QTextFrame>
#include <QTextCharFormat>
#include "atmembertextobject.h"
#include "form.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event);

    bool eventFilter(QObject *watched, QEvent *event);

private slots:
    void on_textEdit_cursorPositionChanged();

    void receiveName(QString name);

    QString getTextBeforeCursor();

private:
    Ui::MainWindow *ui;

    Form *w;
};
#endif // MAINWINDOW_H
