#include <QApplication>
#include <QtGui>
#include <QtCore>
#include <QGraphicsView>
#include "Glyph.h"
#include "Mapping.h"
#include "View.h"

void test_sizeGlyph(QGraphicsScene* scene);
void test_dateGlyph(QGraphicsScene* scene);
void test_timeGlyph(QGraphicsScene* scene);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QGraphicsScene *scene = new QGraphicsScene();
    scene->setSceneRect( 0, 0, 100, 100);
    scene->setBackgroundBrush( Qt::white );
    scene->setItemIndexMethod( QGraphicsScene::NoIndex );
    View *view = new View();
    view->setScene( scene );
    view->show();

    //test_sizeGlyph(scene);
    //test_dateGlyph(scene);
    test_timeGlyph(scene);

    return a.exec();
}

void test_sizeGlyph(QGraphicsScene* scene)
{
    string str = "500 MB";
    string type = tokenise(str, " ").back();
    int    size = atoi(tokenise(str, " ").front().c_str());
    cout << size << type << endl;

    double stop = normalizeScale(256, 0.25, size);
    SizeGlyph *glyph = new SizeGlyph(scene->sceneRect().center(), QSizeF(stop * 80, stop * 80), 0, 1, 3);
    scene->addItem(glyph);
}

void test_dateGlyph(QGraphicsScene* scene)
{
    string str  = "5 Y";
    string type = tokenise(str, " ").back();
    int    age  = atoi(tokenise(str, " ").front().c_str());
    cout << age << type << endl;

    DateGlyph* glyph = new DateGlyph(scene->sceneRect().center(), QSizeF(40, 40), 3, 45);
    scene->addItem(glyph);
}

void test_timeGlyph(QGraphicsScene* scene)
{
    qreal start =0;
    qreal stop = 0;

    stop = normalize(0, 23, 0, 1, 23);

    TimeGlyph* glyph = new TimeGlyph(scene->sceneRect().center(), QSizeF(30, 30), start, stop );
    scene->addItem(glyph);

}
