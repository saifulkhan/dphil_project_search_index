#include "test.h"


test::test (QWidget *parent) :QWidget(parent), ui (new  Ui::TestForm)
{
    ui->setupUi (this);
    scene = new QGraphicsScene (this);
    ui->testView->setScene(scene);


    complexglyph ();
    // zvalue();
}



void test::complexglyph ()
{

}

void test::zvalue()
{
    /*
    PrimaryProperty_S pri;
    pri.color = Qt::magenta; pri.size = 100;
    GlyphDot *c1 = new GlyphDot (pri);
    c1->setZValue(0);
    scene->addItem(c1 );

    PrimaryProperty_S pri1;
    pri1.color = Qt::cyan; pri1.size = 90;
    GlyphDot *c2 = new GlyphDot (pri1);
    c2->setZValue(1);
    c2->setOpacity(.4);
    scene->addItem(c2 );
    */
}

void test::typemapping ()
{
    TypeMapping *m = new TypeMapping;
    m->show ();
}

void test::tf ()
{
    TransferFunction *tf = new TransferFunction;
    tf->show();
}

void test::visualmapping ()
{
    VisualMapping *map = new VisualMapping;
    map->show();
}

void test::colormap()
{
    QGraphicsScene* scene = test::colourMaps();
    QGraphicsView *view = new QGraphicsView; view->setScene(scene );

    view->show();
}

QGraphicsScene* test::colourMaps()
{
    qreal width = 800, height = 600;
    QGraphicsScene *scene = new QGraphicsScene;
    scene->setSceneRect( QRectF(0, 0, width, height) );
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    ColourMap *sunburn = new ColourMap( sunBurnCLUT(), 300.0, 10.0);
    //commented for Qt5
    //sunburn->translate(200.0, 5.0);

    ColourMap *uncert = new ColourMap( uncertaintyCLUT(), 200.0, 20.0);
    //commented for Qt5
    //uncert->translate(200.0, 300.0);

    ColourMap *time = new ColourMap( timeCLUT(), 10.0, 200.0, 0.0, 500.0, 10);
    //commented for Qt5
    //time->translate(500.0, 200.0);

    scene->addText( QString ("Test: Sunburn colormap") );
    scene->addItem( sunburn );
    scene->addItem( uncert );
    scene->addItem( time );

    return scene;
}


void test::modelview()
{
    QStandardItemModel *_model = new QStandardItemModel (8, 3, this);
    _model->setHeaderData(0, Qt::Horizontal, "File Type");
    _model->setHeaderData(1, Qt::Horizontal, "Primary");
    _model->setHeaderData(1, Qt::Horizontal, "Secondary");

    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            QModelIndex index = _model->index(row, col, QModelIndex ());
            _model->setData(index, 0);
        }
    }

//   ui->tableView->setModel(_model);
//   ui->tableView->setIndexWidget(table1->model()->index(0, 1), new GlyphView ());

}




//

//

CircleItem::CircleItem (QGraphicsItem *parent)
{
    _radius = 5.0;
    _scale = 3.0;
}

QRectF CircleItem::boundingRect() const
{
    double rect = _radius * _scale;
    return QRectF (-rect, -rect, 2 * rect, 2 * rect);
}


void CircleItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    QRectF rect ( -_radius, -_radius, 2 * _radius, 2 * _radius);
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen (QPen (Qt::cyan, 2, Qt::SolidLine, Qt::RoundCap));
    painter->drawEllipse (rect);

}

void CircleItem::animate ()
{
    _anim = new QPropertyAnimation (this, "scale");
    _anim->setEasingCurve (QEasingCurve::Linear);
    _anim->setDuration (1000);
    _anim->setStartValue (0);
    _anim->setEndValue (_scale);

    _anim->setLoopCount (-1);
    _anim->start(QAbstractAnimation::DeleteWhenStopped);
}
