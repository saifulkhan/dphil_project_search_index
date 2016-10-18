#include "Secondary.h"
#include "Animation.h"
#include "Glyph.h"
#include "SecondaryGlyph.h"


Secondary::Secondary (GlyphType gtype, QSizeF size, QColor color, qreal pen, QPointF axis)
{
    this->gtype = gtype;
    this->size = size;
    this->color = color;
    this->pen = pen;
    this->axis =  axis;
}

Secondary& Secondary::operator= (const Secondary &p)
{
    this->gtype = p.gtype;
    this->size = p.size;
    this->color = p.color;
    this->pen = p.pen;
    this->axis = p.axis;

    return *this;
}


Secondary::Secondary (const Secondary &p)
{
    this->gtype = p.gtype;
    this->size = p.size;
    this->color = p.color;
    this->pen = p.pen;
    this->axis = p.axis;
}


void Secondary::setType (QString str)
{
    int index = metaObject ()->indexOfEnumerator ("GlyphType");
    QMetaEnum metaEnum = metaObject () ->enumerator (index);
    gtype = (GlyphType) metaEnum.keyToValue (str.toLatin1());
}


QString Secondary::getTypeString () const
{
    int index = metaObject()->indexOfEnumerator ("GlyphType");
    QMetaEnum metaEnum = metaObject()->enumerator (index);
    return metaEnum.valueToKey (gtype);
}


QDebug operator<< (QDebug debug, const Secondary &sec)
{
    debug.nospace() << "Secondary ("
    << sec.gtype << ", "
    << sec.size << ", "
    << sec.color << ", "
    << sec.pen << ", "
    << sec.axis << ")";
    return debug.space();
}


Glyph* instance (const Secondary &sec, const Animation &an)
{
    switch (sec.gtype)
    {
    case 0:
        return new GlyphCircle (sec, an);
    case 1:
        return new GlyphSquare (sec, an);
    case 2:
        return new GlyphEllipse (sec, an);
    case 3:
        return new GlyphTriangle (sec, an);
    case 4:
        return new GlyphClock (sec, an);
    case 5:
        return new GlyphPie (sec, an);
    case 6:
        return new GlyphOrbitar (sec, an);
    default:
        Q_ASSERT (false);
    }
}
