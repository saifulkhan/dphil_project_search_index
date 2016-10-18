#include "Glyph.h"

#include <cstring>
#include <string>

Glyph::~Glyph()
{

}


void Glyph::stopAnimation ()
{
    if (_anim)
    {
        _anim->stop();
        _anim->deleteLater();
        _anim = NULL;
    }
}


void Glyph::startAnimation()
{
    //qDebug() << __PRETTY_FUNCTION__ <<  " property= " <<  _an.getTypeString();

    if (_an.getTypeString() == "null" || _an.tfVector.isEmpty())
        return;
    else if (_anim)
           this->stopAnimation();

    _anim = new QPropertyAnimation(this, _an.getTypeString().toStdString().c_str());
    _anim->setEasingCurve (QEasingCurve::Linear);
    _anim->setDuration (_an.duration);

   _anim->setKeyValues(_deNormalize(_an.start, _an.stop, _an.tfVector));

    _anim->setLoopCount(-1);
    //QObject::connect(_anim, SIGNAL(finished()), this, SLOT(animationFinished()));
    _anim->start(QAbstractAnimation::DeleteWhenStopped);
}


/// convert the scale and create keyValue
QVector <QPair <qreal, QVariant> > Glyph::_deNormalize (const double &min, const double &max, const QVector <QPair <double, double> > &tfVector)
{
    QVector <QPair <qreal, QVariant> > keyValue;
    double delta = max - min;

    for (int i = 0; i < tfVector.size(); i++) {
        double x =  tfVector[i].first;
        double y =  min + ( delta * tfVector[i].second );
        keyValue.push_back( QPair <qreal, QVariant> (x, y));
        //qDebug() << __PRETTY_FUNCTION__ << x << ", " << y << endl;
    }
    return keyValue;
}


qreal Glyph::blink () const
{
    m_blink;
}


void Glyph::setBlink (qreal blink)
{
    // Implemented for primary
}



qreal Glyph::rotationX() const
{
    return m_rotationX;
}


void Glyph::setRotationX(qreal angle)
{
    if (m_rotationX != angle)
    {
        m_rotationX = angle;
        QPointF c = boundingRect().center();
        QTransform t;
        t.translate(c.x(), c.y());
        t.rotate (m_rotationX, Qt::XAxis);
        t.translate(-c.x(), -c.y());
        setTransform(t);
    }
}


qreal Glyph::rotationY() const
{
    return m_rotationY;
}


void Glyph::setRotationY(qreal angle)
{
    if (m_rotationY != angle)
    {
        m_rotationY = angle;
        //QPointF c = boundingRect().center();
        QTransform t;
        //t.translate(c.x(), c.y());
        t.rotate (m_rotationY, Qt::YAxis);
        //t.translate(-c.x(), -c.y());
        setTransform(t);
    }
}


qreal Glyph::rotationZ () const
{
    return m_rotationZ;
}


void Glyph::setRotationZ (qreal angle)
{
    if (m_rotationZ != angle)
    {
        m_rotationZ = angle;
        QPointF c = boundingRect().center();
        QTransform t;
        t.translate(c.x(), c.y());
        t.rotate (m_rotationZ, Qt::ZAxis);
        t.translate(-c.x(), -c.y());
        setTransform(t);
    }
}

void Glyph::animationFinished()
{
}

