#include "Glyph.h"
#include "Mapping.h"


AbstractGlyph::~AbstractGlyph()
{
}


void AbstractGlyph::setupAnimation( QString anType )
{
    //qDebug() << __PRETTY_FUNCTION__ << anType;
    animation = new QPropertyAnimation( this, anType.toStdString().c_str());
    animation->setEasingCurve (QEasingCurve::Linear);
    animation->setDuration(duration);
    animation->setKeyValues( normalizeTF( start, stop, tf));
    animation->setLoopCount(-1);
    //startAnimation();
}


void AbstractGlyph::startAnimation()
{
    animation->start(QAbstractAnimation::KeepWhenStopped);
}


void AbstractGlyph::stopAnimation()
{
    animation->stop();
}


void AbstractGlyph::resetAnimation( QVector<QPair<double, double> > _tf, double _duration, QString anType )
{
    tf.clear();
    tf = _tf;
    duration = _duration;
    if (animation)
        delete animation;
    setupAnimation(anType);
}


/// convert the scale and create keyValue
QVector <QPair <qreal, QVariant> > AbstractGlyph::normalizeTF (const double &min,
                                                               const double &max,
                                                               const QVector <QPair <double, double> > &tf)
{
    QVector <QPair <qreal, QVariant> > keyValue;

    for (int i = 0; i < tf.size(); i++) {
        double x =  tf[i].first;
        double y =  normalize(0, 1, min, max, tf[i].second); // convert (0-1) scale to (min-max) scale
        keyValue.push_back( QPair <qreal, QVariant> (x, y));
    }
    return keyValue;
}


/*
 * Type
 */


TypeGlyph::TypeGlyph (QPointF _center, QSizeF _size, QColor _color, FileInfoX _fileInfo, QGraphicsItem *parent):
    center(_center), size(_size), color(_color), fileInfo( _fileInfo )
{
    this->setPos(center);   // It will be placed in this pos/point after added to scene.
    bound.setWidth( size.width() );
    bound.setHeight( size.height() );
    bound =  QRectF( -bound.width() / 2, -bound.height() / 2, bound.width(), bound.height() );  // Make centre = (0, 0).

    tf << QPair <double, double> (0, 0) <<
          QPair <double, double> (0.00001, 1) <<
          QPair <double, double> (0.7, 1) <<
          QPair <double, double> (0.70001, 0) <<
          QPair <double, double> (1, 0);
    duration = 1500;

    start = 0.0,
    stop = 1.0;
    this->setupAnimation( QString("opacity") );

    //qDebug() << __PRETTY_FUNCTION__ << tf << endl;
    setCacheMode( QGraphicsItem::DeviceCoordinateCache, bound.size().toSize() );
}


TypeGlyph::~TypeGlyph ()
{

}


QRectF TypeGlyph::boundingRect() const
{
    return bound;
}


void TypeGlyph::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = bound;
    //painter->setRenderHints( QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::HighQualityAntialiasing, true );
    painter->setRenderHints( QPainter::Antialiasing, true );
    painter->setPen( Qt::NoPen );
    painter->setBrush(color);
    painter->drawEllipse(rect);

}


void TypeGlyph::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    m_mapping->notifyClickEvent(fileInfo);

    QMessageBox msgBox;
    msgBox.setWindowTitle("Glyph");
    msgBox.setText("File attributes");
    char* size = convertSizeUnit(fileInfo.m_fileInfo.m_size);
    msgBox.setInformativeText(QString( "Path: %1 \nName: %2 \nSize: %3 \nModified: %4" )
                              .arg(QString::fromStdString(fileInfo.m_fileInfo.m_path))
                              .arg(QString::fromStdString(fileInfo.m_fileInfo.m_fileName))
                              .arg(size)
                              .arg(QString::fromStdString(fileInfo.m_fileInfo.m_lastModified)));

    msgBox.setDefaultButton(QMessageBox::Close);
    msgBox.exec();

    delete size;
    //cout << __PRETTY_FUNCTION__ << fileInfo << endl;
    //QGraphicsItem::mousePressEvent (event);
}

void TypeGlyph::registerObserver(Mapping *mapping)
{

    //qDebug() << __PRETTY_FUNCTION__ << endl;
    this->m_mapping = mapping;
}


/*
 * Size
 */


SizeGlyph::SizeGlyph( QPointF _center, QSizeF _size, qreal _start, qreal _stop, int _quadrant, QGraphicsItem *parent) :
    center(_center), size(_size), quadrant(_quadrant)
{
    this->setPos(center);   // It will be placed in this pos/point after added to scene.
    bound.setWidth( size.width() );
    bound.setHeight( size.height() );
    bound =  QRectF( -bound.width() / 2, -bound.height() / 2, bound.width(), bound.height() );  // Make centre = (0, 0).
    //qDebug() << __PRETTY_FUNCTION__ << " Center= " << center << ", Size= " << size << ", bound= " << bound;

    /// Set animation properties
    animation = 0;

    tf << QPair <double, double> (0, 0) <<
          QPair <double, double> (0.00001, 1) <<
          QPair <double, double> (0.7, 1) <<
          QPair <double, double> (0.70001, 0) <<
          QPair <double, double> (1, 0);
    duration = 6000;

    start = _start,
    stop = _stop;
    this->setupAnimation( QString("scale") );

    /*
    start = 0.0,
    stop = 1.0;
    this->setupAnimation( QString("opacity") );
    */

    setCacheMode( QGraphicsItem::DeviceCoordinateCache, bound.size().toSize() );
}


SizeGlyph::~SizeGlyph()
{
}


QRectF SizeGlyph::boundingRect() const
{
    return bound;
}

void SizeGlyph::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF sizeRect = bound;

    int startAngle;
    int spanAngle = -70 * 16;
    switch(quadrant) {
    case 1:
        startAngle = 80 * 16;
        break;
    case 2:
        startAngle = -10 * 16;
        break;
    case 3:
        startAngle = -100 * 16;
        break;
    case 4:
        startAngle = -190 * 16;
        break;
    default:
        Q_ASSERT(false);
    }

    QColor colour(255, 140, 0); // dark orange

    //painter->setRenderHints( QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::HighQualityAntialiasing, true );
    painter->setRenderHints( QPainter::Antialiasing, true );
    painter->setPen(colour);
    painter->setBrush(colour);
    painter->drawPie(sizeRect, startAngle, spanAngle);

    //qDebug() << __PRETTY_FUNCTION__;
}


/*
 * Time
 */

TimeGlyph::TimeGlyph( QPointF _center, QSizeF _size, qreal _start, qreal _stop, QGraphicsItem *parent) :
    center(_center), size(_size)
{
    this->setPos(center);   // It will be placed in this pos/point after added to scene.
    bound.setWidth( size.width() );
    bound.setHeight( size.height() );
    bound =  QRectF(-bound.width() / 2, -bound.height() / 2, bound.width(), bound.height());

    day       = new ColourMap( dayCLUT(), 500.0, 100);
    // Set animation properties
    animation = NULL;
    start     = _start;
    stop      = _stop;
    m_length  = stop;
    duration  = 6000;

    tf << QPair <double, double> (0, 0) <<
          QPair <double, double> (0.1, 0) <<
          QPair <double, double> (0.10001, 1) <<
          QPair <double, double> (0.8, 1) <<
          QPair <double, double> (0.80001, 0) <<
          QPair <double, double> (1, 0);

    this->setupAnimation( QString("length") );;
    setCacheMode( QGraphicsItem::DeviceCoordinateCache, bound.size().toSize() );
}


TimeGlyph::~TimeGlyph()
{
    delete animation;
}


QRectF TimeGlyph::boundingRect() const
{
    return bound;
}


void TimeGlyph::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF sizeRect = bound;

    double rx;
    double dx;
    double ry;
    double dy;
    rx = dx = bound.center().x();
    ry = dy = bound.center().y();

    double offset = 8;
    double radius = sizeRect.height() / 2 - offset; // starting radius, will grow till +offset.

    //painter->setRenderHints( QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::HighQualityAntialiasing, true );
    painter->setRenderHints( QPainter::Antialiasing, true );

    for (double i = 0; i <= m_length; i = i + 0.02 )
    {
        double angle = normalize( 0, 1, 0, 4* PI, i );  // convert i (0-1) scale to (0- 4pi) scale. Same below.
        double _radius = normalize( 0, 1, radius, radius + offset, i );

        #ifdef DBG_GLYPH
        qDebug() << __PRETTY_FUNCTION__ << "i= " << i << ", angle= " << angle << ", radious= " << _radius;
        #endif

        double x = rx + sin( angle ) * _radius;
        double y = ry - sin( angle + PI / 2 ) * _radius;

        if (!(i == 0)) {
            QPen pen(QBrush(day->lookup( i ), Qt::SolidPattern), 1.5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
            painter->setPen(pen);
            painter->drawLine( QLineF(x, y, dx, dy) );
        }
        dx = x;
        dy = y;
    }
}


qreal TimeGlyph::length() const
{
    return m_length;
}


void TimeGlyph::setLength(qreal length)
{
    if (this->m_length != length) {
            this->m_length = length;
            this->update();
    }
}


/*
 * Date
 */

DateGlyph::DateGlyph( QPointF _center, QSizeF _size, int _quadrant, qreal _rotate, QGraphicsItem *parent )
    : center(_center), size(_size), quadrant(_quadrant), rotate(_rotate)
{
    this->setPos(center);   // It will be placed in this pos/point after added to scene.
    bound.setWidth( size.width() );
    bound.setHeight( size.height() );
    bound =  QRectF( -bound.width() / 2, -bound.height() / 2, bound.width(), bound.height() );  // Make centre = (0, 0).

    // Set animation properties
    animation = NULL;
    start     = 0;
    stop      = rotate;
    m_rotationZ = rotate;

    duration  = 6000;
    tf  << QPair <double, double> (0, 0) <<
          QPair <double, double> (0.2, 0) <<
          QPair <double, double> (0.20001, 1) <<
          QPair <double, double> (0.9, 1) <<
          QPair <double, double> (0.90001, 0) <<
          QPair <double, double> (1, 0);

    this->setupAnimation( QString("rotationZ") );
    setCacheMode( QGraphicsItem::DeviceCoordinateCache, bound.size().toSize() );

    #ifdef DBG_GLYPH
    qDebug() << __PRETTY_FUNCTION__ << "start->stop" << start << "->" << stop;
    #endif
}


DateGlyph::~DateGlyph()
{
    delete animation;
}


QRectF DateGlyph::boundingRect() const
{
    return bound;
}


void DateGlyph::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    qreal ringwidth = 5.0;
    QRectF sizeRect = bound;
    sizeRect.adjust(ringwidth / 2, ringwidth / 2, - ringwidth / 2, -ringwidth / 2);

    int startingPos = 0;
    switch(quadrant)
    {
        case 1:
            startingPos = 90;
            break;
        case 2:
            startingPos = 0;
            break;
        case 3:
            startingPos = -90;
            break;
        case 4:
            startingPos = -180;
            break;
        default:
            Q_ASSERT(false);
    }

    painter->setRenderHints( QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::HighQualityAntialiasing, true );
    //painter->setRenderHints( QPainter::Antialiasing, true );
    QColor color = Qt::cyan;

    //outer ring
    painter->setOpacity(0.4);
    painter->setPen( QPen( QBrush(Qt::gray, Qt::SolidPattern), ringwidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin ) );
    painter->drawArc( sizeRect, 0 * 16, 360 * 16 );

    // Arc
    painter->setOpacity(1.0);
    painter->setPen( QPen( QBrush( color, Qt::SolidPattern), ringwidth, Qt::SolidLine, Qt::FlatCap, Qt::RoundJoin ) );
    painter->drawArc(sizeRect, startingPos * 16, -m_rotationZ * 16);

    #ifdef DBG_GLYPH
    cout << startingPos << ", " << -m_rotationZ << endl;
    #endif
}


qreal DateGlyph::rotationZ () const
{
   return m_rotationZ;
}


void DateGlyph::setRotationZ (qreal angle)
{
    if (this->m_rotationZ != angle)
    {
        this->m_rotationZ = angle;
        this->update();
    }
}


/*
 * Permission
 */

PermissionGlyph::PermissionGlyph(QPointF _center, QSizeF _size, QGraphicsItem *parent ) :
    center(_center), size(_size)
{
    this->setPos(center);   // It will be placed in this pos/point after added to scene.
    bound.setWidth( size.width() );
    bound.setHeight( size.height() );
    bound =  QRectF( -bound.width() / 2, -bound.height() / 2, bound.width(), bound.height() );  // Make centre = (0, 0).
    //qDebug() << __PRETTY_FUNCTION__ << " Center= " << center << ", Size= " << size << ", bound= " << bound;

    /// Set animation properties
    animation = NULL;
    start = 0;
    stop = 1;
    duration = 6000;
    tf << QPair <double, double> (0, 0) << QPair <double, double> (0.25, 1) << QPair <double, double> (0.75, 1) << QPair <double, double> (0.7501, 0) << QPair <double, double> (1, 0);
    this->setupAnimation( QString("opacity") );

    setCacheMode( QGraphicsItem::DeviceCoordinateCache, bound.size().toSize() );
}


PermissionGlyph::~PermissionGlyph()
{
    delete animation;
}


QRectF PermissionGlyph::boundingRect() const
{
   return bound;
}


void PermissionGlyph::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF sizeRect = bound;

    //painter->setRenderHints( QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::HighQualityAntialiasing, true );
    painter->setRenderHints( QPainter::Antialiasing, true );

    // The cross - 2 gray lines
    QPainterPath line;
    line.moveTo( 0, sizeRect.height() / 2 );
    line.lineTo( 0, -sizeRect.height() / 2 );
    painter->setPen(Qt::gray);
    //painter->save();                              // TODO: commented time being
    painter->rotate(-45);
    painter->drawPath(line);
    //painter->rotate(90);                          // TODO: commented time being
    painter->drawPath(line);
    //painter->restore();

    // Ticks
    int offset = bound.height() / 5;
    int l = 5;

    QPainterPath user;
    painter->rotate(-45);
    for (int i = 0; i < 3; i++) {
        user.moveTo( -l / 2, -sizeRect.height() / 2 + offset * i );
        user.lineTo(  l / 2, -sizeRect.height() / 2 + offset * i );
        //colorcheck
        //if set orange, else gray
        painter->setPen(QColor(255, 165, 0));
        painter->drawPath(user);
    }

    QPainterPath group;
    for (int i = 0; i < 3; i++) {
        group.moveTo( -(l + 4) / 2, +sizeRect.height() / 2 - offset * i);
        group.lineTo(  (l + 4) / 2, +sizeRect.height() / 2 - offset * i);
        //colorcheck
        //if set orange, else gray
        painter->setPen(QColor(255, 165, 0));
        painter->drawPath(group);
    }

    painter->rotate(90);
    QPainterPath other;
    for (int i = 0; i < 3; i++) {
        other.moveTo( -(l + 2) / 2, -sizeRect.height() / 2 + offset * i);
        other.lineTo( +(l + 2) / 2, -sizeRect.height() / 2 + offset * i);
        //colorcheck
        //if set orange, else gray
        painter->setPen(QColor(255, 165, 0));
        painter->drawPath(other);
    }

    QPainterPath diamond;

}
