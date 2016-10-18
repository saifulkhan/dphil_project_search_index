#include "SecondaryGlyph.h"
#include "Secondary.h"
#include "Animation.h"

SecondaryGlyph::~SecondaryGlyph ()
{

}


void SecondaryGlyph::setup (Secondary s, Animation a)
{
    _sec = s;
    _an = a;

    this->setPos (_sec.axis.x(), _sec.axis.y());

    // bounding rectengle maximum scale times higher
    if (_an.getTypeString() == "Scale")
    {
        qreal scaling = _an.start > _an.stop ?  _an.start : _an.stop;

        _bound.setHeight (_sec.size.height() * scaling);
        _bound.setWidth (_sec.size.width() * scaling);
    }
    else
    {
        _bound.setHeight (_sec.size.height());
        _bound.setWidth (_sec.size.width());
    }

    //this->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
    //this->hide();
    _anim = NULL;
    this->startAnimation();
}

///////////////////////////////////////////////////////////////////////////////
//
// GlyphCircle : SecondaryGlyph
//
///////////////////////////////////////////////////////////////////////////////

GlyphCircle::GlyphCircle (Secondary sec, Animation an, QGraphicsItem *parent)
{
    setup (sec, an);

    this->setFlag (QGraphicsItem::ItemIgnoresTransformations);
}



GlyphCircle::~GlyphCircle ()
{

}

QRectF GlyphCircle::boundingRect() const
{
    return QRectF ( -(_bound.height() + _sec.pen / 2), -(_bound.width() + _sec.pen / 2),
                    (2 * _bound.height() + _sec.pen / 2), (2 * _bound.width() + _sec.pen / 2) );
}


void GlyphCircle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    qreal radius = _sec.size.height();
    QRectF rect ( -(radius + _sec.pen / 2), -(radius + _sec.pen / 2), (2 * radius + _sec.pen / 2), (2 * radius + _sec.pen / 2));
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen (QPen (_sec.color, _sec.pen, Qt::SolidLine, Qt::RoundCap));
    painter->setBrush (_sec.color);       // TODO
    painter->drawEllipse (rect);

}


///////////////////////////////////////////////////////////////////////////////
//
// GlyphSquare : SecondaryGlyph
//
///////////////////////////////////////////////////////////////////////////////

GlyphSquare::GlyphSquare (Secondary statProperty, Animation anProperty, QGraphicsItem *parent)
{
    setup (statProperty, anProperty);
}

GlyphSquare::~GlyphSquare ()
{

}

QRectF GlyphSquare::boundingRect() const
{
    return QRectF ( -(_bound.height() + _sec.pen / 2), -(_bound.width() + _sec.pen / 2),
                    (2 * _bound.height() + _sec.pen / 2), (2 * _bound.width() + _sec.pen / 2) );
}


void GlyphSquare::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    double side = _sec.size.height();

    QRectF rect ( -(side + _sec.pen/2), -(side + _sec.pen),
                  (2 * side + _sec.pen), (2 * side + _sec.pen));
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen (QPen (_sec.color, 1, Qt::SolidLine, Qt::RoundCap));
    painter->drawRect (rect);
}


///////////////////////////////////////////////////////////////////////////////
//
// GlyphEllipse : SecondaryGlyph
//
///////////////////////////////////////////////////////////////////////////////

GlyphEllipse::GlyphEllipse (Secondary statProperty, Animation anProperty, QGraphicsItem *parent)
{
    setup (statProperty, anProperty);
}

GlyphEllipse::~GlyphEllipse ()
{

}

QRectF GlyphEllipse::boundingRect() const
{
    return QRectF ( -(_bound.height() + _sec.pen / 2), -(_bound.width() + _sec.pen / 2),
                    (2 * _bound.height() + _sec.pen / 2), (2 * _bound.width() + _sec.pen / 2) );
}


void GlyphEllipse::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    double side = _sec.size.height();

    QRectF rect ( -(side + _sec.pen), -(side / 2 + _sec.pen),
                  (2 * side + _sec.pen), (2 * side / 2 + _sec.pen));
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen (QPen (_sec.color, 1, Qt::SolidLine, Qt::RoundCap));
    painter->drawEllipse (rect);
}


///////////////////////////////////////////////////////////////////////////////
//
// GlyphTriangle : SecondaryGlyph
//
///////////////////////////////////////////////////////////////////////////////

GlyphTriangle::GlyphTriangle (Secondary statProperty, Animation anProperty, QGraphicsItem *parent)
{
    setup (statProperty, anProperty);
}

GlyphTriangle::~GlyphTriangle ()
{

}

QRectF GlyphTriangle::boundingRect() const
{
    return QRectF ( -(_bound.height() + _sec.pen / 2), -(_bound.width() + _sec.pen / 2),
                    (2 * _bound.height() + _sec.pen / 2), (2 * _bound.width() + _sec.pen / 2) );
}


void GlyphTriangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    double side = _sec.size.height();

    QRectF rect ( -(side + _sec.pen), -(side + _sec.pen),
                  (2 * side + _sec.pen), (2 * side + _sec.pen));


    QPolygon polygon (3);
    polygon.setPoint (0, rect.center().x(), rect.top());
    polygon.setPoint (1, rect.right(), rect.bottom());
    polygon.setPoint (2, rect.left(), rect.bottom());


    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen (QPen (_sec.color, 1, Qt::SolidLine, Qt::RoundCap));
    painter->drawPolygon (polygon);
}


///////////////////////////////////////////////////////////////////////////////
//
// GlyphClock : SecondaryGlyph
//
///////////////////////////////////////////////////////////////////////////////

GlyphClock::GlyphClock (Secondary sec, Animation an, QGraphicsItem *parent)
{
     setup (sec, an);
}

GlyphClock::~GlyphClock ()
{

}


QRectF GlyphClock::boundingRect() const
{
    return QRectF ( -(_bound.height() + _sec.pen / 2), -(_bound.width() + _sec.pen / 2),
                    (2 * _bound.height() + _sec.pen / 2), (2 * _bound.width() + _sec.pen / 2) );
}


void GlyphClock::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPainterPath pathC;
    pathC.moveTo (0, 0);
    pathC.addEllipse (this->boundingRect());
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen (QPen (_sec.color, _sec.pen, Qt::SolidLine, Qt::RoundCap));
    painter->drawPath (pathC);

    QPainterPath pathL;
    pathL.moveTo (0, 0);
    pathL.lineTo (0, - _bound.height());
    painter->setPen (QPen (_sec.color, _sec.pen, Qt::SolidLine, Qt::RoundCap));
    painter->drawPath (pathL);
}


///////////////////////////////////////////////////////////////////////////////
//
// GlyphPie : SecondaryGlyph
//
///////////////////////////////////////////////////////////////////////////////

GlyphPie::GlyphPie (Secondary sec, Animation an, QGraphicsItem *parent)
{
     setup (sec, an);
    _radius = _sec.size.height();
}

GlyphPie::~GlyphPie ()
{

}

QRectF GlyphPie::boundingRect() const
{
    return QRectF ( -(_bound.height() + _sec.pen / 2), -(_bound.width() + _sec.pen / 2),
                    (2 * _bound.height() + _sec.pen / 2), (2 * _bound.width() + _sec.pen / 2) );
}


void GlyphPie::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    qreal tick = 5; // 5 pixel width

    /// This part is the transparent guide.
    QPainterPath outerCircle;
    outerCircle.moveTo (0, 0);
    outerCircle.addEllipse (-_radius, -_radius, 2 * _radius,  2* _radius);

    QPainterPath innerCircle;
    qreal r = _radius - tick;
    innerCircle.moveTo (0, 0);
    innerCircle.addEllipse( -r, -r, 2 * r,  2* r);

    QPainterPath guide = outerCircle.subtracted(innerCircle);

    painter->setOpacity(0.15);
    painter->setRenderHint(QPainter::Antialiasing);
    painter->fillPath(guide, _sec.color);
    painter->setOpacity(1);


    /// This part is the arch. Deduct a inner circle from outer pie/arch
    QPainterPath outer;
    outer.setFillRule(Qt::OddEvenFill);
    outer.moveTo (0, 0);
    outer.arcTo (-_radius, -_radius, 2 * _radius,  2* _radius, 90, -m_rotationZ);

    QPainterPath inner;
    //qreal r = _radius - tick;
    inner.moveTo (0, 0);
    inner.addEllipse( -r, -r, 2 * r,  2* r);

    QPainterPath fillPath = outer.subtracted(inner);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->fillPath(fillPath, _sec.color);
    //painter->strokePath (inner, QPen (_sec.color, 1, Qt::DashLine) ); // Draw a outer dashed circle as a guide.

    //qDebug() << __PRETTY_FUNCTION__ << -m_rotationZ;
}

qreal GlyphPie::rotationZ () const
{
   return m_rotationZ;
}

void GlyphPie::setRotationZ (qreal angle)
{
    //qDebug() << "GlyphClock::setClock: " << angle << ", " << m_rotationZ;
    if (this->m_rotationZ != angle)
    {
        this->m_rotationZ = angle;
        this->update();
    }
}


///////////////////////////////////////////////////////////////////////////////
//
// GlyphOrbitar : SecondaryGlyph
//
//////////////////////////////////////////////////////////////////////////////


GlyphOrbitar::GlyphOrbitar (Secondary sec, Animation an, QGraphicsItem *parent)
{
    orbitarRadius = 5;
    setup (sec, an);
}

GlyphOrbitar::~GlyphOrbitar ()
{

}

QRectF GlyphOrbitar::boundingRect() const
{
    return QRectF ( -(_bound.height() + orbitarRadius + _sec.pen / 2), -(_bound.width() + orbitarRadius + _sec.pen / 2),
                    2 * ( _bound.height() + orbitarRadius + _sec.pen / 2), 2 * (_bound.width() + orbitarRadius + _sec.pen / 2) );
}


void GlyphOrbitar::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    // Background a circle (dial)
    QPainterPath pathC;
    pathC.moveTo (0, 0);
    pathC.addEllipse (this->boundingRect());
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen (QPen (_sec.color, _sec.pen, Qt::SolidLine, Qt::RoundCap));
    painter->drawPath (pathC);

    // The dot at the orbitar edge
    QPainterPath path2;
    path2.addEllipse ( 0, - (_bound.height() + orbitarRadius), orbitarRadius, orbitarRadius);
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen (QPen (_sec.color, _sec.pen, Qt::SolidLine, Qt::RoundCap));
    painter->setBrush (_sec.color);
    painter->drawPath (path2);


}

///////////////////////////////////////////////////////////////////////////////
//
// GlyphPixmap : Glyph
//
///////////////////////////////////////////////////////////////////////////////

#if 0
GlyphPixmap::GlyphPixmap (GlyphProperty property, const QPixmap &pixmap, QGraphicsItem *parent) : Glyph (property, 0, color, parent)
{
    _pixmap = pixmap;
    _sizeF = sizeF;
}

QRectF GlyphPixmap::boundingRect () const
{
    return QRectF ( -(4 * _sizeF.width () + 0.5), -(4 * _sizeF.height () + 0.5), (8 * _sizeF.width () + 0.5), (8 * _sizeF.height () + 0.5) );
}

void GlyphPixmap::paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint (QPainter::Antialiasing);
    painter->drawPixmap (QPointF (-_bound, -_bound), _pixmap);
}


QString GlyphPixmap::getShapeType ()
{
    qDebug() << "GlyphPixmap" << endl;
    return "GlyphPixmap";
}

#endif

