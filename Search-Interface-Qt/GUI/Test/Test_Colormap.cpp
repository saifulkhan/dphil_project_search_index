#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include "ColourMap.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qreal width = 800, height = 600;
    QGraphicsScene *scene = new QGraphicsScene;
    scene->setSceneRect( QRectF(0, 0, width, height) );
    QGraphicsView *view = new QGraphicsView( scene );
    view->show();



    ColourMap *sunburn = new ColourMap( sunBurnCLUT(), 300.0, 10.0);
    //commented for Qt5
    //sunburn->translate(200.0, 5.0);
    //scene->addItem( sunburn );

    ColourMap *uncert = new ColourMap( uncertaintyCLUT(), 600.0, 700.0);
    //commented for Qt5
    //uncert->translate(200.0, 300.0);
    //scene->addItem( uncert );

    ColourMap *day = new ColourMap( dayCLUT(), 500.0, 100);
    //commented for Qt5
    //time->translate(500.0, 200.0);

    ColourMap *treemapF = new ColourMap( treemapFCLUT(), 500.0, 100);
    treemapF->setPos( 10, 10);
    scene->addItem( treemapF );

    ColourMap *treemapD = new ColourMap( treemapDCLUT(), 300.0, 100.0);
    treemapD->setPos( 400, 400);
    scene->addItem( treemapD );

    return a.exec();
}
