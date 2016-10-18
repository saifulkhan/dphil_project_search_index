#ifndef GLYPH_H
#define GLYPH_H

#include <QObject>
#include <QGraphicsItem>
#include <QPropertyAnimation>
#include <QGraphicsSceneMouseEvent>
#include <QParallelAnimationGroup>

#include "../GlobalVariables.h"

class Animation;

class Glyph : public QObject, public QGraphicsItem
{
    Q_OBJECT

    Q_PROPERTY (qreal opacity READ opacity WRITE setOpacity)
    Q_PROPERTY (qreal blink READ blink WRITE setBlink)
    // Q_PROPERTY (qreal fade READ fade WRITE setFade)              // Pixmap ???
    Q_PROPERTY (qreal scale READ scale WRITE setScale)
    Q_PROPERTY (qreal rotationX READ rotationX WRITE setRotationX)
    Q_PROPERTY (qreal rotationY READ rotationY WRITE setRotationY)
    Q_PROPERTY (qreal rotationZ READ rotationZ WRITE setRotationZ)
    // Q_PROPERTY (qreal shutter READ shutter WRITE setShutter)     // in GlyphShutter ??

protected:
    Animation _an;
    QSizeF _bound;

    QPropertyAnimation* _anim;
    qreal m_blink, m_blur, m_rotationX, m_rotationY, m_rotationZ, m_shutter;

public slots:
    virtual void animationFinished();

public:
    ~Glyph () = 0;

    virtual void startAnimation ();
    virtual void stopAnimation ();
    virtual QVector <QPair <qreal, QVariant> > _deNormalize (const double &, const double &,
                                                             const QVector <QPair <double, double> > &);

    virtual qreal blink () const;
    virtual void setBlink (qreal blink);
//    virtual qreal fade () const;
//    virtual void setfade (qreal blur);
    virtual qreal rotationX () const;
    virtual void setRotationX (qreal angle);
    virtual qreal rotationY () const;
    virtual void setRotationY (qreal angle);
    virtual qreal rotationZ () const;
    virtual void setRotationZ (qreal angle);
//    virtual qreal shutter ();
//    virtual void setShutter (qreal);

};



#endif // GLYPH_H
