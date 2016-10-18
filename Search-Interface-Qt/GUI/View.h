#ifndef VIEW_H
#define VIEW_H

#include <QDebug>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QtOpenGL/QGLWidget>
 


class View : public QGraphicsView
{
    Q_OBJECT
 
protected:
    virtual void paintEvent ( QPaintEvent * event );
    //virtual void keyPressEvent( QKeyEvent *event );
    //virtual void drawBackground ( QPainter *painter, const QRectF &rect );
    //virtual void drawForeground ( QPainter *painter, const QRectF &rect );
    //virtual void mousePressEvent ( QMouseEvent * event );
    //virtual void mouseReleaseEvent ( QMouseEvent *event );
    //virtual void wheelEvent(QWheelEvent* event);
    //virtual void resizeEvent ( QResizeEvent *event );

public:
    View( QWidget* parent = 0 );
    ~View();
    //void setItem( QGraphicsTileItem *item );
};

#endif
