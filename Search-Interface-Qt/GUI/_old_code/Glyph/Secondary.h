#ifndef SECONDARY_H
#define SECONDARY_H

#include <QtCore>
#include <QObject>
#include <QColor>

class SecondaryGlyph;
class Animation;
class Glyph;


// TODO: This should be in GlobalVariables.h. For time being it is here.

#define SEC_DEF_SIZE 8        // Default
#define SEC_MAX_SIZE 125
#define DEF_COLOR Qt::cyan


class Secondary : public QObject
{
    Q_OBJECT
    Q_ENUMS (GlyphType)

public:
    enum  GlyphType {Circle, Square, Ellipse, Triangle, Clock, Pie, Orbitar};

    GlyphType gtype;
    QSizeF size;        //TODO: Qpolygonf / qvector <qpointf> () << qpointf(10,20) << ... ??
    QColor color;
    qreal pen;
    QPointF axis;

    Secondary (GlyphType gtype = Circle, QSizeF size = QSizeF (SEC_DEF_SIZE, SEC_DEF_SIZE),
               QColor color = DEF_COLOR, qreal pen = 2, QPointF axis = QPointF () );

    Secondary &operator= (const Secondary &);
    Secondary (const Secondary &);

    void setType (QString);
    QString getTypeString () const;

    friend QDebug operator<< (QDebug debug, const Secondary &);
    friend Glyph* instance (const Secondary &, const Animation &);

};

QDebug operator<< (QDebug debug, const Secondary &);
Glyph* instance (const Secondary &, const Animation &);

namespace dev
{
    class Secondary;
}
#endif // SECONDARY_H
