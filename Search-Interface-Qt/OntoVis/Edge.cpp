#include <QPainter>

 #include "Edge.h"
 #include "Node.h"

 #include <math.h>

 static double TwoPi = 2.0 * M_PI;

 Edge::Edge(Node *sourceNode, Node *destNode, QString edge_weight) : arrowSize(5)
 {
     m_edge_weight = edge_weight;
     setAcceptedMouseButtons(0);
     source = sourceNode;
     dest = destNode;
     source->addEdge(this);
     dest->addEdge(this);
     adjust();
 }

 Node *Edge::sourceNode() const
 {
     return source;
 }

 Node *Edge::destNode() const
 {
     return dest;
 }

 void Edge::adjust()
 {
     if (!source || !dest)
         return;

     QLineF line(mapFromItem(source, 0, 0), mapFromItem(dest, 0, 0));
     qreal length = line.length();

     prepareGeometryChange();

     if (length > qreal(20.)) {
         QPointF edgeOffset((line.dx() * 10) / length, (line.dy() * 10) / length);
         sourcePoint = line.p1() + edgeOffset;
         destPoint = line.p2() - edgeOffset;
     } else {
         sourcePoint = destPoint = line.p1();
     }
 }

 QRectF Edge::boundingRect() const
 {
     if (!source || !dest)
         return QRectF();

     qreal penWidth = 1;
     qreal extra = (penWidth + arrowSize) / 2.0;

     return QRectF(sourcePoint, QSizeF(destPoint.x() - sourcePoint.x(),
                                       destPoint.y() - sourcePoint.y()))
         .normalized()
         .adjusted(-extra, -extra, extra, extra);
 }

 void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
 {
     if (!source || !dest)
         return;

     QLineF line(sourcePoint, destPoint);
     if (qFuzzyCompare(line.length(), qreal(0.)))
         return;

     // Draw the line itself
     painter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
     painter->drawLine(line);

     // Draw the arrows
     double angle = ::acos(line.dx() / line.length());
     if (line.dy() >= 0)
         angle = TwoPi - angle;

     QPointF sourceArrowP1 = sourcePoint + QPointF(sin(angle + M_PI / 3) * arrowSize, cos(angle + M_PI / 3) * arrowSize);
     QPointF sourceArrowP2 = sourcePoint + QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize, cos(angle + M_PI - M_PI / 3) * arrowSize);
     QPointF destArrowP1   = destPoint   + QPointF(sin(angle - M_PI / 3) * arrowSize, cos(angle - M_PI / 3) * arrowSize);
     QPointF destArrowP2   = destPoint   + QPointF(sin(angle - M_PI + M_PI / 3) * arrowSize, cos(angle - M_PI + M_PI / 3) * arrowSize);

     painter->setBrush(Qt::black);
     //painter->drawPolygon(QPolygonF() << line.p1() << sourceArrowP1 << sourceArrowP2);
     painter->drawPolygon(QPolygonF() << line.p2() << destArrowP1 << destArrowP2);


    // Write the weight
    float factor = boundingRect().width() / (6 * painter->fontMetrics().width(m_edge_weight));
    if ((factor < 1) || (factor > 1.25))
    {
        QFont f = painter->font();
        f.setPointSizeF(f.pointSizeF()*factor);
        painter->setFont(f);
    }

    int x = (sourcePoint.x() +  destPoint.x()) / 2;
    int y = (sourcePoint.y() +  destPoint.y()) / 2;
    painter->drawText(x, y, m_edge_weight);
}
