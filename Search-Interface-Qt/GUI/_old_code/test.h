#ifndef TEST_H
#define TEST_H

#include <QtCore>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QDebug>
#include <QVector>


#include "Ui/PrimaryForm.h"
#include "Ui/SecondaryForm.h"
#include "Ui/AnimationForm.h"
#include "Ui/VisWindow.h"

#include "Glyph/PrimaryGlyph.h"
#include "Glyph/SecondaryGlyph.h"

#include "TF/TransferFunction.h"

#include "ColourMap/ColourMap.h"
#include "Mapping/TypeMapping.h"
#include "Mapping/VisualMapping.h"


#include "ui_TestForm.h"

class test : public QWidget
{
    Q_OBJECT

signals:

public slots:

private:
     Ui::TestForm *ui;
     QGraphicsScene *scene;

public:
    explicit test(QWidget *parent = 0);

    void complexglyph ();
    void glyphAndAnimation ();
    void zvalue();

    QGraphicsScene* colourMaps();
    void anpropertywidget ();
    void viswindow ();

    void colormap();
    void tf ();
    void typemapping ();
    void visualmapping ();
    void modelview();

    void psychologyTest ();
    
};


class CircleItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_PROPERTY (qreal scale READ scale WRITE setScale)

private:
    qreal _radius;
    qreal _scale;
    QPropertyAnimation *_anim;

public:
    CircleItem (QGraphicsItem *parent = 0);
    ~CircleItem ()
    {
    }

    QRectF boundingRect () const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

    void animate ();
};


#endif // TEST_H
