/**
  * TODO: Change to GlyphEditorView
  **/

#ifndef GlyphView_H
#define GlyphView_H

#include <iostream>
#include <vector>
#include <QDebug>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QGraphicsItem>
#include <QPointF>
#include <QStyleOptionGraphicsItem>
//#include <QGLWidget>

#include "../GUI/Ui/PrimaryDialog.h"
#include "../GUI/Ui/SecondaryDialog.h"


class Secondary;
class Animation;
class Glyph;
class PrimaryGlyph;
class SecondaryGlyph;


using namespace std;

class GlyphView : public QGraphicsView
{
  Q_OBJECT

private:
    qreal _width, _height;

    QGraphicsScene *_scene;
    PrimaryProperty_S _pri;
    Secondary _sec;
    Animation _an;

    Glyph *_priGlyph, *_secGlyph;
    QGraphicsPixmapItem *_treemap, *_treemapItem;

    PrimaryDialog *_priDialog;
    SecondaryDialog *_secDialog;


protected:
    virtual void drawBackground ( QPainter *painter, const QRectF &rect );
    virtual void drawForeground ( QPainter *painter, const QRectF &rect );
    virtual void mousePressEvent ( QMouseEvent * event );
    virtual void mouseReleaseEvent ( QMouseEvent *event );

public slots:
    void addPrimary (PrimaryProperty_S pri = PrimaryProperty_S () );
    void addSecondary (Secondary sec = Secondary (), Animation an = Animation () );


public:
    GlyphView (QWidget* parent = 0x0);
    virtual ~GlyphView();
    void setupScene (qreal width = 100, qreal height = 100);
    void addTreemap (const QString &);
    void addTreemapItem (const QString &, const qreal);
    void addTextItem (QGraphicsTextItem *text, qreal size);

    PrimaryProperty_S getPriProperty ();
    Secondary getSecProperty ();
    Animation getAnProperty ();

};





#endif // GlyphView_H
