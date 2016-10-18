#include "TransferFunction.h"


///////////////////////////////////////////////////////////////////////////////
//
//  Point : QGraphicsItem
//
///////////////////////////////////////////////////////////////////////////////

Point::Point (TransferFunction* parent ) :
    _radius ( 2.0 ), _left ( 0x0 ), _right ( 0x0 ), _parent ( parent )
{
    this->setFlag ( QGraphicsItem::ItemIsMovable );
}


Point::~Point()
{

}


///  Set the point to the left.

void Point::left ( Point* point )
{
    this->_left = point;
}


///  Get the point to the left.

Point* Point::left() const
{
  return this->_left;
}


///  Set the point to the right.

void Point::right ( Point* point )
{
    this->_right = point;
}


///  Get the point to the right.

Point* Point::right() const
{
    return this->_right;
}


///  Get the bounding rectangle.

QRectF Point::boundingRect() const
{
    return QRectF (-_radius, -_radius, 2 * _radius, 2 * _radius );
}


///  Paint.

void Point::paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRadialGradient gradient ( 0.0, 0.0, _radius );

    // If we are selected, use a lighter color.
    if ( option->state & QStyle::State_Sunken) {
        gradient.setColorAt ( 0, QColor ( Qt::magenta ).light ( 120 ) );
        gradient.setColorAt ( 1, QColor ( Qt::darkBlue ).light ( 120 ) );
        painter->setPen ( QPen ( Qt::red, 0 ) );
    } else {
        gradient.setColorAt ( 0, Qt::yellow );
        gradient.setColorAt ( 1, Qt::darkYellow );
        painter->setPen ( QPen ( Qt::black, 0 ) );
    }

    painter->setBrush ( gradient );
    painter->drawEllipse ( -_radius, -_radius, 2 * _radius, 2 * _radius);
}


///  The item has changed.

QVariant Point::itemChange(GraphicsItemChange change, const QVariant &value)
{
    switch (change)
    {
    case ItemPositionHasChanged:
        if ( _parent != 0x0 )
            _parent->forceRedraw();
        break;

    default:
        break;
    };

  return QGraphicsItem::itemChange(change, value);
}


///  The mouse has moved.

void Point::mouseMoveEvent ( QGraphicsSceneMouseEvent *event )
{
    this->update();
    QGraphicsItem::mouseMoveEvent(event);

    QRectF boundingBox ( this->scene()->sceneRect() );

    // Reset our x position if we are one of the end points.
    if ( _left == 0x0 )
        this->setPos ( 0, this->pos().y() );

    if ( _right == 0x0 )
        this->setPos ( boundingBox.x() + boundingBox.width(), this->pos().y() );

    this->_clampToRectangle ( boundingBox );
    this->_clampToLeftAndRight();
}


///  A mouse button has been pressed.

void Point::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    this->update ();
    QGraphicsItem::mousePressEvent (event);
}


///  A mouse button has been released.

void Point::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    this->update();
    QGraphicsItem::mouseReleaseEvent(event);
}


///  Clamp so that this point is still between the left and the right.

void Point::_clampToLeftAndRight()
{
    if ( _left != 0x0 )
    {
        if ( this->pos().x() <= _left->pos().x() )
        {
            this->setPos ( _left->pos().x() + 1, this->pos().y() );
        }
    }

    if ( _right != 0x0 )
    {
        if ( this->pos().x() >= _right->pos().x() )
        {
            this->setPos ( _right->pos().x() - 1, this->pos().y() );
        }
    }
}


///  Clamp the position to the given rectangle.

void Point::_clampToRectangle ( const QRectF& rectangle )
{
    qreal x = this->pos().x();
    qreal y = this->pos().y();

    const qreal xMin = rectangle.x();
    const qreal xMax = xMin + rectangle.width();
    const qreal yMin = rectangle.y();
    const qreal yMax = yMin + rectangle.height();

    x = qMax ( x, xMin );
    x = qMin ( x, xMax );

    y = qMax ( y, yMin );
    y = qMin ( y, yMax );

    this->setPos ( x, y );
}



///////////////////////////////////////////////////////////////////////////////
//
// TransferFunction : QGraphicsView
//
///////////////////////////////////////////////////////////////////////////////



TransferFunction::TransferFunction ( QWidget* parent ) :
    QGraphicsView ( parent ), _scene ( 0x0 ), _first ( 0x0 ), _last  ( 0x0 )
{
  const int xMin ( 0 );
  const int yMin ( 0 );
  const int xMax ( 400 );
  const int yMax ( 100 );

  this->setViewportUpdateMode ( QGraphicsView::FullViewportUpdate );
  this->setCacheMode(CacheNone);
  this->setRenderHint(QPainter::Antialiasing);
  this->setTransformationAnchor(AnchorUnderMouse);
  this->setResizeAnchor(AnchorViewCenter);
  _scene = new QGraphicsScene ( this );
  _scene->setItemIndexMethod(QGraphicsScene::NoIndex);
  _scene->setSceneRect ( xMin, yMin, xMax, yMax );
  _scene->setBackgroundBrush( QBrush(Qt::white, Qt::SolidPattern) );

  this->setScene ( _scene );

  Point* first = new Point ( this );
  Point* last = new Point ( this );

  // Hook up linked list.
  first->right ( last );
  last->left ( first );

  _scene->addItem ( first );
  _scene->addItem ( last );

  first->setPos ( xMin, yMax );
  last->setPos ( xMax, yMax );

  _first = first;
  _last = last;
}


///  Destructor.

TransferFunction::~TransferFunction()
{
    Point *current ( _first );
    while ( 0x0 != current )
    {
        std::cout << "[" << current->pos().x() << "," << current->pos().y() << "]" << std::endl;
        current = current->right();
    }
}


///  Draw the background.

void TransferFunction::drawBackground ( QPainter *painter, const QRectF &rect )
{
    QRectF sceneRect = this->sceneRect();

    const qreal xMin = sceneRect.x();
    const qreal xMax = xMin + sceneRect.width();
    const qreal yMin = sceneRect.y();
    const qreal yMax = yMin + sceneRect.height();

    // Draw the border.
    painter->setPen( QPen( QBrush(Qt::gray), 0, Qt::SolidLine ) );
    //painter->drawRect ( sceneRect );

    // Grids - draw the ticks
    int ticks = 5;
    int dx = sceneRect.width() / ticks;
    int dy = sceneRect.height() / ticks;
    painter->setPen( QPen( QBrush(Qt::gray), 0, Qt::DotLine ) );
    for ( int t = 0; t <= ticks; ++t ) {
        qreal xPos = t * dx;
        painter->drawLine ( QLineF ( QPointF ( xMin + xPos, yMin ), QPointF ( xMin + xPos, yMax ) ) );

        qreal yPos = t * dy;
        painter->drawLine ( QLineF ( QPointF ( xMin, yMin + yPos ), QPointF ( xMax, yMin + yPos ) ) );

    }
}


///  Draw the line between the items (Point).

void TransferFunction::drawForeground(QPainter *painter, const QRectF &rect)
{
    painter->setRenderHint ( QPainter::Antialiasing );
    painter->setPen ( QPen ( Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin ) );

    Point *current =  _first;
    while ( current != 0x0 && current->right() != 0x0)
    {
        painter->drawLine ( current->pos(), current->right()->pos() );
        current = current->right();
    }

    QGraphicsView::drawForeground (painter, rect);
}

///  Force a redraw.

void TransferFunction::forceRedraw()
{
    QRectF viewport ( _scene->sceneRect() );
    _scene->invalidate ( viewport );
    this->update();

    this->_updateTransferFunction();
}

QVector <QPair <double, double> > TransferFunction::getTransferFunction ()
{
    return _tfVector;
}


///  A mouse button has been pressed.

void TransferFunction::mousePressEvent ( QMouseEvent * event )
{
    //qDebug () << "Mouse pressing in view..." << endl;

    if ( event->buttons().testFlag ( Qt::LeftButton ) == true)
    {
        if (QGraphicsItem *item = itemAt(event->pos())) {
            //qDebug() << "You clicked on item" << item;
        } else {
            //qDebug() << "You didn't click on an item.";

            Point *point = new Point ( this );
            _scene->addItem( point );

            QPointF position = this->mapToScene ( event->pos() );
            point->setPos ( position );

            // Find the point to the left of the position.
            Point *left ( this->_findPointOnLeft( position ) );
            if ( left )
            {
                Point* temp = left->right();

                // Set the new right point.
                left->right( point );

                // Set the pointers for our new point.
                point->left( left );
                point->right( temp );
            }
        }
    }

    else if ( event->buttons().testFlag ( Qt::MidButton ) == true)
    {
        Point *current = _first->right();

        while ( current != 0x0 && current != _last)
        {
            _scene->removeItem ( current );
            delete current;

            current = current->right();
        }

        // Hook up linked list.
        _first->right (_last);
        _last->left (_first);
    }

    QGraphicsView::mousePressEvent ( event );
}


///  A mouse button has been released.

void TransferFunction::mouseReleaseEvent ( QMouseEvent *event )
{
    //qDebug () << "Mouse release in view..." << endl;
    this->forceRedraw ();
}


void TransferFunction::resizeEvent(QResizeEvent *event)
{
    if (_scene)
    {
        // _scene->setSceneRect ( QRect ( QPoint (0, 0), event->size() ) );
    }
    QGraphicsView::resizeEvent (event);
}


///  Find the point to the left of position.

Point* TransferFunction::_findPointOnLeft ( QPointF position )
{
    Point *current = _first;
    while ( current != 0x0 && current->right() != 0x0 )
    {
        Point* right =  current->right();
        if ( right->pos().x() > position.x() )
        {
            return current;
        }

        current = right;
    }

    return 0x0;
}


///  Update the transfer function.

void TransferFunction::_updateTransferFunction()
{
    double nx = 0, ny = 0;
    _tfVector.clear();

    QRectF sceneRectangle = _scene->sceneRect();
    const qreal xMin = sceneRectangle.x();
    const qreal yMin = sceneRectangle.y();
    const qreal yMax = yMin + sceneRectangle.height();

    Point *current = _first;
    while ( current != 0x0 )
    {
        const double x = current->pos().x();
        const double y = current->pos().y();

        nx = ( x - xMin ) / sceneRectangle.width();
        ny = ( yMax - y ) / sceneRectangle.height();
        _tfVector.push_back ( QPair <double, double> (nx, ny) );

        current = current->right();
    }

#if 0
    // Debug part
    for (int i = 0; i < _tfVector.size (); i++)
    {
        qDebug () << "(" << _tfVector[i].first << ", " << _tfVector[i].second << ")";
    }
    qDebug() << endl;
#endif

}


///  Set the transfer function.

void TransferFunction:: setTransferFunction( QVector <QPair <double, double> > tfVector )
{
    // Clear what we have.
    _scene->clear();
    _first = 0x0;
    _last = 0x0;
    _tfVector.clear();

    _tfVector = tfVector;

    QRectF sceneRectangle = _scene->sceneRect();
    const qreal xMin = sceneRectangle.x();
    const qreal xMax = xMin + sceneRectangle.width();
    const qreal yMin = sceneRectangle.y();
    const qreal yMax = yMin + sceneRectangle.height();

    Point* firstItem = new Point ( this );
    Point* lastItem = new Point ( this );

    // Hook up linked list.
    firstItem->right ( lastItem );
    lastItem->left ( firstItem );

    _scene->addItem ( firstItem );
    _scene->addItem ( lastItem );


/*
    firstItem->setPos ( xMin, yMax - ( yMax * firstIterator->second ) );
    lastItem->setPos ( xMax, yMax - ( yMax * lastIterator->second ) );

    Point* previousItem ( firstItem );

    OpacityMap::const_iterator currentIterator ( ++opacities.begin() );
    while ( currentIterator != lastIterator )
    {
      const double u ( static_cast<double> ( currentIterator->first - firstIterator->first ) / ( lastIterator->first - firstIterator->first ) );
      const double x ( xMin + ( sceneRectangle.width() * u ) );
      const double y ( yMax - ( yMax * currentIterator->second ) );

      Point* point ( new Point ( this ) );
      point->setPos ( x, y );
      _scene->addItem ( point );

      previousItem->right ( point );
      point->left ( previousItem );
      previousItem = point;

      ++currentIterator;
    }

    lastItem->left ( previousItem );

    _first = firstItem;
    _last = lastItem;
*/

}

