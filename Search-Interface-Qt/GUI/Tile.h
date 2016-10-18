#ifndef TILE_H
#define TILE_H

#include <QGraphicsItem>
#include <QtGui>
#include <QMessageBox>
#include <QStyleOptionGraphicsItem>

#include <Conversion.h>
#include <FileInfo.h>

#include "Layout.h"

#define TREEMAP_FONT_SIZE 6

class Tile : public QGraphicsItem
{
private:
    const FileInfo fileInfo;
    const int depth;
    const int maxdepth;
    const QRectF bound;
    QColor colour;
    QColor lastcolour;
    QPen pen;

    QColor getColour();
    QColor blendColor( QColor a, QColor b, qreal alpha );

public:

    Tile(FileInfo fileInfo, int depth, int maxdepth, QRectF bound, QGraphicsItem *parent = 0);
    //Tile(NodeTM* node, int maxdepth, QGraphicsItem *parent = 0);
    ~Tile ();
    QRectF boundingRect () const;
    void paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0 );
    void mousePressEvent( QGraphicsSceneMouseEvent * );
    //void hoverEnterEvent(QGraphicsSceneHoverEvent *);
    //void hoverLeaveEvent(QGraphicsSceneHoverEvent *);
};


#endif //
