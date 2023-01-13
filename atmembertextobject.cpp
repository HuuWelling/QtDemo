#include "atmembertextobject.h"

QSizeF AtMemberTextObject::intrinsicSize(QTextDocument *doc, int posInDocument, const QTextFormat &format)
{
    Q_UNUSED(doc)
    Q_UNUSED(posInDocument)

    QString txt = qvariant_cast<QString>(format.property(AtData));
    QFont font = qvariant_cast<QFont>(format.property(AtFont));
    QFontMetrics *m_pmf = new QFontMetrics(font);

    return QSizeF(m_pmf->size(Qt::AlignCenter,txt));
}

void AtMemberTextObject::drawObject(QPainter *painter, const QRectF &rect, QTextDocument *doc, int posInDocument, const QTextFormat &format)
{
    Q_UNUSED(doc)
    Q_UNUSED(posInDocument)
    QString txt = qvariant_cast<QString>(format.property(AtData));

    painter->fillRect(rect,QBrush(QColor("#00ffff")));
    painter->drawText(rect,txt);
}
