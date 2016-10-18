#ifndef SECONDARYGLYPH_H
#define SECONDARYGLYPH_H

#include "Glyph.h"

class Secondary;
class Animation;

class SecondaryGlyph : public Glyph
{

protected:
    Secondary _sec;


public:
    ~SecondaryGlyph() = 0;
    virtual void setup (Secondary sec, Animation an);

};




///////////////////////////////////////////////////////////////////////////////
//
// GlyphCircle : SecondaryGlyph
//
///////////////////////////////////////////////////////////////////////////////

class GlyphCircle : public SecondaryGlyph
{

private:

public:
    GlyphCircle (Secondary statProperty, Animation anProperty, QGraphicsItem *parent = 0);
    ~GlyphCircle ();

    QRectF boundingRect () const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
};




///////////////////////////////////////////////////////////////////////////////
//
// GlyphSquare : SecondaryGlyph
//
///////////////////////////////////////////////////////////////////////////////

class GlyphSquare : public SecondaryGlyph
{
private:


public:
    GlyphSquare (Secondary statProperty, Animation anProperty, QGraphicsItem *parent = 0);
    ~GlyphSquare ();

    QRectF boundingRect () const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
};




///////////////////////////////////////////////////////////////////////////////
//
// GlyphEllipse : SecondaryGlyph
//
///////////////////////////////////////////////////////////////////////////////

class GlyphEllipse : public SecondaryGlyph
{
private:


public:
    GlyphEllipse (Secondary statProperty, Animation anProperty, QGraphicsItem *parent = 0);
    ~GlyphEllipse ();

    QRectF boundingRect () const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
};




///////////////////////////////////////////////////////////////////////////////
//
// GlyphTriangle : SecondaryGlyph
//
///////////////////////////////////////////////////////////////////////////////

class GlyphTriangle : public SecondaryGlyph
{
private:


public:
    GlyphTriangle (Secondary statProperty, Animation anProperty, QGraphicsItem *parent = 0);
    ~GlyphTriangle ();

    QRectF boundingRect () const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
};



///////////////////////////////////////////////////////////////////////////////
//
// GlyphClock : SecondaryGlyph
//
///////////////////////////////////////////////////////////////////////////////

class GlyphClock : public SecondaryGlyph
{

public:
    enum
    {
        GlyphClockType = UserType + 1
    };

    int type () const
    {
        return GlyphClockType;
    }

    GlyphClock (Secondary, Animation, QGraphicsItem *parent = 0);
    ~GlyphClock ();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

};



///////////////////////////////////////////////////////////////////////////////
//
// GlyphPie : SecondaryGlyph
//
//////////////////////////////////////////////////////////////////////////////

class GlyphPie : public SecondaryGlyph
{

private:
    qreal _radius;

public:

    GlyphPie (Secondary, Animation, QGraphicsItem *parent = 0);
    ~GlyphPie ();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

    virtual qreal rotationZ () const;
    virtual void setRotationZ (qreal angle);

};


///////////////////////////////////////////////////////////////////////////////
//
// GlyphOrbitar : SecondaryGlyph
//
//////////////////////////////////////////////////////////////////////////////

class GlyphOrbitar : public SecondaryGlyph
{
private:
    qreal orbitarRadius;

public:

    GlyphOrbitar (Secondary, Animation, QGraphicsItem *parent = 0);
    ~GlyphOrbitar ();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

};

///////////////////////////////////////////////////////////////////////////////
//
// GlyphPixmap : Glyph
// QPixmap pixmap (":/Resources/other/sun.png"); GlyphPixmap *pic = new GlyphPixmap (pixmap.size(), pixmap);
///////////////////////////////////////////////////////////////////////////////

#if 0
class GlyphPixmap : public Glyph
{
    //Q_PROPERTY(int fade READ fade WRITE setFade)
private:
    QPixmap _pixmap;
    QSizeF _sizeF;

public:

    GlyphPixmap (GlyphProperty property, const QPixmap &pixmap, QGraphicsItem *parent = 0);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

    //void* getSize ();
    QString getShapeType ();

};
#endif


#endif // SECONDARYGLYPH_H
