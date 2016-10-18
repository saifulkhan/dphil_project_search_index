#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QGraphicsView>

#include <iostream>
#include <map>
#include <math.h>

using namespace std;

class Node;

class GraphWidget : public QGraphicsView
{
    Q_OBJECT

private:
    QGraphicsScene* m_scene;
    int             timerId;
    Node*           m_centerNode;

public:
    GraphWidget(QWidget *parent = 0);
    ~GraphWidget();
    void addItems(const string& root, map<string, double> nodes);
    void itemMoved();


public slots:
    void shuffle();
    void zoomIn();
    void zoomOut();

protected:
    void keyPressEvent(QKeyEvent *event);
    void timerEvent(QTimerEvent *event);
    void wheelEvent(QWheelEvent *event);
    void drawBackground(QPainter *painter, const QRectF &rect);

    void scaleView(qreal scaleFactor);
};

#endif
