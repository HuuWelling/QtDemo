#ifndef ATMEMBERTEXTOBJECT_H
#define ATMEMBERTEXTOBJECT_H

#include <QTextObjectInterface>
#include <QFontMetrics>
#include <QPainter>
#include <QFont>

QT_BEGIN_NAMESPACE
class QTextDocument;
class QTextFormat;
class QPainter;
class QRectF;
class QSizeF;
QT_END_NAMESPACE

enum { AtTextFormat = QTextFormat::UserObject + 1 };
enum AtTextProperties { AtData = QTextFormat::UserProperty + 1 , AtFont ,AtUserId };

class AtMemberTextObject : public QObject, public QTextObjectInterface
{
    Q_OBJECT
    Q_INTERFACES(QTextObjectInterface)
public:
    QSizeF intrinsicSize(QTextDocument *doc, int posInDocument,
                         const QTextFormat &format) override;
    void drawObject(QPainter *painter, const QRectF &rect, QTextDocument *doc,
                    int posInDocument, const QTextFormat &format) override;

};

#endif // ATMEMBERTEXTOBJECT_H
