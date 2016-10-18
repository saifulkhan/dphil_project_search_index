#ifndef EDGE_H
#define EDGE_H

#include <QGraphicsItem>

class Node;

class Edge : public QGraphicsItem
{
private:
    Node *source, *dest;

    QPointF sourcePoint;
    QPointF destPoint;
    qreal arrowSize;
    QString m_edge_weight;

public:
    enum { Type = UserType + 2 };
    int type() const { return Type; }


    Edge(Node *sourceNode, Node *destNode, QString edge_weight);
    Node *sourceNode() const;
    Node *destNode() const;
    void adjust();

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

};

#endif
