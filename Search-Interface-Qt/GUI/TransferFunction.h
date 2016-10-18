#ifndef TRANSFERFUNCTION_H
#define TRANSFERFUNCTION_H

#include <iostream>
#include <QDebug>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QGraphicsItem>
#include <QPointF>
#include <QStyleOptionGraphicsItem>
#include <QtOpenGL/QGLWidget>

using namespace std;

class Point;
class TransferFunction;


// Refer: http://code.google.com/p/heliosvolume/source/browse/trunk/Source/#Source%2FQt%2FTransferFunction

///////////////////////////////////////////////////////////////////////////////
//
//  Point
//
///////////////////////////////////////////////////////////////////////////////


class Point : public QGraphicsItem
{

private:

    double _radius;
    Point *_left;
    Point *_right;

    TransferFunction *_parent;

protected:

    QVariant itemChange ( GraphicsItemChange change, const QVariant &value );
    void mouseMoveEvent ( QGraphicsSceneMouseEvent *event );
    void mousePressEvent ( QGraphicsSceneMouseEvent *event );
    void mouseReleaseEvent ( QGraphicsSceneMouseEvent *event );

    void _clampToRectangle ( const QRectF& rectangle );
    void _clampToLeftAndRight();

public:

    Point ( TransferFunction* parent = 0 );
    virtual ~Point();

    // Set/get the point to the left.
    void left ( Point* point );
    Point* left() const;

    // Set/get the point to the right.
    void right ( Point* point );
    Point* right() const;

    virtual QRectF boundingRect() const;
    void paint ( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0 );

};



///////////////////////////////////////////////////////////////////////////////
//
// TransferFunction : QGraphicsView
//
///////////////////////////////////////////////////////////////////////////////

class TransferFunction : public QGraphicsView
{
  Q_OBJECT

private:

    QVector <QPair <double, double> > _tfVector;

    QGraphicsScene *_scene;
    Point *_first;
    Point *_last;


protected:

    virtual void drawBackground ( QPainter *painter, const QRectF &rect );
    virtual void drawForeground ( QPainter *painter, const QRectF &rect );
    virtual void mousePressEvent ( QMouseEvent * event );
    virtual void mouseReleaseEvent ( QMouseEvent *event );
    virtual void resizeEvent ( QResizeEvent *event );

    Point* _findPointOnLeft ( QPointF position );
    void _updateTransferFunction();


public:

    TransferFunction ( QWidget* parent = 0x0 );
    virtual ~TransferFunction();
    void forceRedraw();

    QVector <QPair <double, double> > getTransferFunction ();
    void setTransferFunction( QVector <QPair <double, double> > tfVector );
};


#endif // TRANSFERFUNCTION_H
