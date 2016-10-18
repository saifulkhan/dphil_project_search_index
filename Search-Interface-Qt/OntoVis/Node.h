#ifndef NODE_H
#define NODE_H

#include <QGraphicsItem>
#include <QList>

class Edge;
class GraphWidget;
class QGraphicsSceneMouseEvent;

class Node : public QGraphicsItem
{
private:
    QList<Edge*>    edgeList;
    QPointF         newPos;
    GraphWidget*    graph;
    QString         m_node_name;

public:
    enum { Type = UserType + 1 };

    Node(QString node_name, GraphWidget *graphWidget);
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void addEdge(Edge *edge);
    QList<Edge *> edges() const;
    int type() const { return Type; }
    void calculateForces();
    bool advance();

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif
