#include "PrimaryGlyph.h"


PrimaryGlyph::PrimaryGlyph (PrimaryProperty_S pri, Animation an, QGraphicsItem *parent)
{
    _pri = pri;
    _an = an;
    m_color = _pri.color;

    this->setPos (_pri.axis.x(), _pri.axis.y());

    _anim = NULL;
    this->startAnimation();
}

PrimaryGlyph::~PrimaryGlyph ()
{
}

QRectF PrimaryGlyph::boundingRect() const
{
    return QRectF ( -(_pri.size + 0.5), -(_pri.size + 0.5),
                    (2 * _pri.size + 0.5), (2 * _pri.size + 0.5) );
}


void PrimaryGlyph::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    double radious = _pri.size;

    QRectF rect ( -(radious + 0.5), -(radious + 0.5),
                  (2 * radious + 0.5), (2 * radious + 0.5));

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setBrush ( QBrush (m_color, _pri.style) );
    painter->setPen (QPen (m_color, 1, Qt::SolidLine, Qt::RoundCap));
    painter->drawEllipse (rect);
}


void PrimaryGlyph::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    /*initialPos = mapToScene(event->pos());
    QGraphicsItem::mousePressEvent(event);
    */
}


qreal PrimaryGlyph::blink () const
{
    return m_blink;
}

void PrimaryGlyph::setBlink (qreal blink)
{
    if (m_blink != blink)
    {
        m_blink = blink;

        //float value = min ( max (0.0f, 1.0f - m_blink), 1.0f);
        //float valueExp;

        /*//value = toHr (value, valueExp, m_highRange);
        valueExp = 1.0f;
        if (highRange > 1.0f)
        {
            value *= 2.0f;

            if (value > 1.0f)
            {
                valueExp = pow(highRange, value - 1.0f);
                value = 1.0f;
            }
        }
        */
        //qDebug() << "value = " << m_blink << endl;
        QColor baseColor = _pri.color;
        QColor color = QColor::fromHsvF (baseColor.hueF(), baseColor.saturationF(), m_blink, baseColor.alphaF());
        m_color = color;

        //_pri.color = Qt::red;
        this->update ();
    }

}

