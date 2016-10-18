#include "View.h"

View::View(QWidget* parent ) : QGraphicsView( parent )
{
    this->setRenderHint(QPainter::Antialiasing, false);         // Note: Not all the glyphs/treemap-tiles are antialiazed
    this->setResizeAnchor(QGraphicsView::AnchorViewCenter);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setDragMode(QGraphicsView::RubberBandDrag);
    this->setOptimizationFlags(QGraphicsView::DontSavePainterState);
    this->setViewportUpdateMode( QGraphicsView::SmartViewportUpdate);
    this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    this->setCacheMode(QGraphicsView::CacheBackground);
    this->setViewportUpdateMode(QGraphicsView::MinimalViewportUpdate);

    if (false) {
        this->setViewport(new QGLWidget( QGLFormat()));
    }

}


View::~View( )
{

}


void View::paintEvent(QPaintEvent *event)
{
    QPaintEvent *newEvent=new QPaintEvent(event->region().boundingRect());
    QGraphicsView::paintEvent(newEvent);
    delete newEvent;
}

 