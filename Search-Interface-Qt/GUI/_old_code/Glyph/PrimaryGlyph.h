#ifndef PRIMARYGLYPH_H
#define PRIMARYGLYPH_H

#include "Glyph.h"

class PrimaryGlyph : public Glyph
{

private:
    PrimaryProperty_S _pri;
    QColor m_color;

public:
    PrimaryGlyph (PrimaryProperty_S pri = PrimaryProperty_S (), Animation an = Animation (), QGraphicsItem *parent = 0);
    ~PrimaryGlyph ();

    QRectF boundingRect () const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    virtual qreal blink () const;
    virtual void setBlink (qreal blink);

};

#endif // PRIMARYGLYPH_H
