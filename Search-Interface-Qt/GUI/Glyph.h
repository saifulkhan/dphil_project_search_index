#ifndef ABSTRACTGLYPH_H
#define ABSTRACTGLYPH_H

#include <QObject>
#include <QGraphicsItem>
#include <QPropertyAnimation>
#include <QGraphicsSceneMouseEvent>
#include <QParallelAnimationGroup>
#include <QDebug>
#include <QPainter>
#include <QMessageBox>
#include "FileInfo.h"
#include "Conversion.h"
#include "ColourMap.h"

class Mapping;

#define PI 3.14159265359

const int typeGlyphType = QGraphicsItem::UserType + 1;
const int sizeGlyphType = QGraphicsItem::UserType + 2;
const int timeGlyphType = QGraphicsItem::UserType + 3;
const int permissionGlyphType = QGraphicsItem::UserType + 4;
const int dateGlyphType = QGraphicsItem::UserType + 5;

class AbstractGlyph : public QObject, public QGraphicsItem
{

protected:
    double start;
    double stop;
    double duration;
    QVector <QPair <double, double> > tf;
    QPropertyAnimation* animation;

    virtual void setupAnimation( QString anType = "null");
    virtual QVector <QPair <qreal, QVariant> > normalizeTF (const double &start,
                                                  const double &stop,
                                                  const QVector <QPair <double, double> > &tf);
public:
    ~AbstractGlyph() = 0;
    void startAnimation();
    void stopAnimation();
    void resetAnimation( QVector <QPair <double, double> > tf, qreal duration, QString anType );
};


/*
 *
 */


class TypeGlyph : public AbstractGlyph
{
    Q_OBJECT
    Q_PROPERTY (qreal scale READ scale WRITE setScale)
    Q_PROPERTY (qreal opacity READ opacity WRITE setOpacity)

private:
    const QPointF center;
    const QSizeF size;
    const QColor color;
    FileInfoX fileInfo;
    QRectF bound;
    QPropertyAnimation *animation;

    Mapping *m_mapping;

public:
    enum {Type = typeGlyphType};
    TypeGlyph (QPointF center, QSizeF size, QColor color, FileInfoX fileInfo, QGraphicsItem *parent = 0);
    ~TypeGlyph ();

    QRectF boundingRect () const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    void registerObserver(Mapping *Mapping);

};


/*
 *
 */

class SizeGlyph : public AbstractGlyph
{
    Q_OBJECT
    Q_PROPERTY (qreal scale READ scale WRITE setScale)
    Q_PROPERTY (qreal opacity READ opacity WRITE setOpacity)

private:
    const QPointF center;
    const QSizeF size;
    const int quadrant;
    QRectF bound;
    QPropertyAnimation *animation;

public:
    enum {Type = sizeGlyphType};
    SizeGlyph(QPointF axis, QSizeF size, qreal start, qreal stop, int quadrant, QGraphicsItem *parent = 0);
    ~SizeGlyph();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
};


/*
 *
 */

class TimeGlyph : public AbstractGlyph
{
    Q_OBJECT
    Q_PROPERTY (qreal length READ length WRITE setLength)

private:
    const QPointF center;
    const QSizeF size;

    QRectF bound;
    ColourMap *day;
    QPropertyAnimation *animation;
    qreal m_length;

    qreal length() const;
    void setLength(qreal angle);

public:
    enum {Type = timeGlyphType};
    TimeGlyph( QPointF center, QSizeF size, qreal start, qreal stop, QGraphicsItem *parent = 0 );
    ~TimeGlyph();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
};


/*
 *
 */


class PermissionGlyph : public AbstractGlyph
{
    Q_OBJECT
    Q_PROPERTY (qreal opacity READ opacity WRITE setOpacity)

private:
    const QPointF center;
    const QSizeF size;

    QRectF bound;
    QPropertyAnimation *animation;

public:
    enum {Type = permissionGlyphType};
    explicit PermissionGlyph(QPointF center, QSizeF size, QGraphicsItem *parent = 0);
    ~PermissionGlyph();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
};


/*
 *
 */


class DateGlyph : public AbstractGlyph
{
    Q_OBJECT
    Q_PROPERTY (qreal rotationZ READ rotationZ WRITE setRotationZ)

private:
    const QPointF center;
    const QSizeF size;
    int quadrant;
    qreal rotate;

    QRectF bound;
    QPropertyAnimation *animation;
    qreal m_rotationZ;

    qreal rotationZ () const;
    void setRotationZ (qreal angle);

public:
    enum {Type = dateGlyphType};
    DateGlyph( QPointF center, QSizeF size, int quadrant, qreal rotate, QGraphicsItem *parent = 0 );
    ~DateGlyph();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
};
#endif //
