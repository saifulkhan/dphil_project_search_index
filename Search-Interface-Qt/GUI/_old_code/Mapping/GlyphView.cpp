#include "GlyphView.h"

#include "Glyph/Secondary.h"
#include "Glyph/Animation.h"
#include "Glyph/Glyph.h"
#include "Glyph/PrimaryGlyph.h"
#include "Glyph/SecondaryGlyph.h"


GlyphView::GlyphView (QWidget* parent) : QGraphicsView (parent),
    _scene (NULL), _priGlyph (NULL), _secGlyph(NULL), _treemap (NULL), _treemapItem (NULL)
{
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setupScene();
    addPrimary();
    addSecondary();

     _priDialog = new  PrimaryDialog ();
    connect (_priDialog, SIGNAL (PrimaryDialog_Signal (PrimaryProperty_S) ), this, SLOT (addPrimary (PrimaryProperty_S)) );
    _secDialog = new SecondaryDialog ();
    connect (_secDialog, SIGNAL (SecondaryDialog_Signal (Secondary, Animation) ), this, SLOT (addSecondary (Secondary, Animation) ) );
}

void GlyphView::setupScene (qreal width, qreal height)
{
    _width = width;
    _height = height;

    if (!_scene)
    {
         _scene = new QGraphicsScene ( this );
    }

    _scene->setSceneRect (0, 0, _width, _height );
    this->setScene ( _scene );
}


///  Destructor.

GlyphView::~GlyphView()
{

}


///  Draw the background.

void GlyphView::drawBackground ( QPainter *painter, const QRectF &rect )
{
    QRectF sceneRect = this->sceneRect();

    // Draw the border.
    painter->setPen ( QPen ( Qt::black, 2 ) );
   //painter->setBrush ( Qt::lightGray );
    painter->drawRect ( sceneRect );
}


///  Draw the line between the items (Point).

void GlyphView::drawForeground(QPainter *painter, const QRectF &rect)
{
    QGraphicsView::drawForeground (painter, rect);
}


///  A mouse button has been pressed.

void GlyphView::mousePressEvent ( QMouseEvent * event )
{
    qDebug () << "GlyphView::Mouse pressed..." << endl;

    if ( event->buttons().testFlag ( Qt::RightButton ) == true)
    {
        _secDialog->show();
    }

    if ( event->buttons().testFlag ( Qt::LeftButton ) == true)
    {
        _priDialog->show();
    }

    QGraphicsView::mousePressEvent ( event );
}


///  A mouse button has been released.

void GlyphView::mouseReleaseEvent ( QMouseEvent *event )
{
    qDebug () << "Mouse release in view..." << endl;

    QRectF viewport ( _scene->sceneRect() );
    _scene->invalidate ( viewport );
    this->update();
}


///

void GlyphView::addPrimary (PrimaryProperty_S pri)
{
    _pri = pri;

    if (_priGlyph)
    {
        _scene->removeItem(_priGlyph);
        delete _priGlyph;
    }

    _priGlyph = new PrimaryGlyph (_pri);
    _priGlyph->setPos(_width / 2, _height / 2);

    _scene->addItem (_priGlyph);


}


void GlyphView::addSecondary (Secondary sec, Animation an)
{
    _sec = sec;
    _an = an;

    if (_secGlyph)
    {
        _scene->removeItem (_secGlyph);
        delete _secGlyph;
    }

    _secGlyph = instance (_sec, _an);
    _secGlyph->setPos(_width / 2, _height / 2);
    _secGlyph->setZValue(3);
    _scene->addItem (_secGlyph);
}


void GlyphView::addTreemap (const QString &url)
{

    if (_treemap)
    {
        _scene->removeItem(_treemap);
        delete _treemap;

    }

    QPixmap pixmap = QPixmap (url);
    _treemap = _scene->addPixmap (pixmap.scaled ( QSize ((int)_scene->width(), (int)_scene->height()), Qt::KeepAspectRatio, Qt::SmoothTransformation ) );
    _treemap->setPos ( _scene->sceneRect().x(), _scene->sceneRect().y() );

}


void GlyphView::addTreemapItem (const QString &url, qreal size)
{
    if (_treemapItem)
    {
        _scene->removeItem(_treemapItem);
        delete _treemapItem;
    }

    QPixmap pixmap = QPixmap (url);
    _treemapItem = _scene->addPixmap(pixmap);
    _treemapItem->setPos ( _scene->sceneRect().center().x() - (size / 2), _scene->sceneRect().center().y() - (size / 2) );
    _treemapItem->setZValue(2);
}


void GlyphView::addTextItem (QGraphicsTextItem *text, qreal size)
{
   _scene->addItem (text);
   text->setPos ( _scene->sceneRect().center().x(), _scene->sceneRect().center().y() );
   text->setZValue(2);
}


PrimaryProperty_S GlyphView::getPriProperty()
{
    return _pri;
}

Secondary GlyphView::getSecProperty()
{
    return _sec;
}

Animation GlyphView::getAnProperty()
{
    return _an;
}




