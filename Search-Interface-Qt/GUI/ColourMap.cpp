#include "ColourMap.h"


ColourMap::ColourMap(ColourLookUp clut, qreal w,   qreal h,
                     qreal min, qreal max, qreal ticks, QGraphicsItem *parent) : myCLUT(clut), myWidth(w), myHeight(h),
                     myMin(min), myMax(max), myTicks(ticks)
{
    
    mySpan = myMax - myMin;
    this->setParentItem (parent);
    this->annotate ();
}


ColourMap::~ColourMap()
{

}


const QColor ColourMap::lookup (qreal value)
{
    QColor colour256;
    colour256.setRgbF( myCLUT.red(value),
                       myCLUT.green(value),
                       myCLUT.blue(value)   );
    return colour256;
}


const QColor ColourMap::lookupRGB (qreal value, qreal min, qreal max)
{
    qreal nx =  (value - min) / (max - min); // 0-1

    QColor colour256;
    colour256.setRgbF ( myCLUT.red (nx),
                        myCLUT.green (nx),
                        myCLUT.blue (nx)
                       );
    return colour256;
}

const QColor ColourMap::lookupHSV (qreal value, qreal min, qreal max)
{
    qreal nx =  (value - min) / (max - min); // 0-1

    QColor colour256;
    colour256.setHsvF ( value, min, max);
    return colour256;
}


QRectF ColourMap::boundingRect() const
{
    return QRectF(0.0, 0.0, myWidth, myHeight);
}


void ColourMap::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    qDebug() << "painting colourmap";

    qreal dv  = 1.0   / (myMax - myMin);

    if( myWidth > myHeight )
    {
        qreal dx  = myWidth / (myMax - myMin - 1.0);
        qreal dt  = myWidth / myTicks;
        qreal x   = 0.0;
        painter->setPen( QPen( Qt::NoPen ) );
        // draw the bars in the colour map
        for( qreal value = 0.0; value <= 1.0; value+= dv)
        {
            QColor c = this->lookup( value );
            painter->setBrush( QBrush( c ) );
            painter->drawRect( QRectF(x,0,dx*1.1, myHeight) );
            x+=dx;
        }

        painter->setPen( QPen(Qt::black) );
        painter->setBrush( QBrush(Qt::NoBrush) );
        // draw the ticks
        for( int t = 0; t < myTicks+1; ++t )
        {
            qreal tPos = t * dt;
            painter->drawLine( QLineF( QPointF(tPos - dx*0.5, 0.0), QPointF(tPos - dx*0.5, myHeight + 5.0) ) );
        }

    }
    else
    {
        qreal dy  = myHeight / (myMax - myMin - 1.0);
        qreal dt  = myHeight / myTicks;
        qreal y   = myHeight - 1.0;
        painter->setPen( QPen( Qt::NoPen ) );
        // draw the bars in the colour map
        for( qreal value = 0.0; value <= 1.0; value+= dv)
        {
            QColor c = this->lookup( value );
            painter->setBrush( QBrush( c ) );
            painter->drawRect( QRectF(0,y, myWidth, dy*1.5) );
            y-=dy;
        }

        painter->setPen( QPen(Qt::black) );
        painter->setBrush( QBrush(Qt::NoBrush) );
        // draw the ticks
        for( int t = myTicks; t > -1; --t ){
            qreal tPos = t * dt;
            painter->drawLine( QLineF( QPointF(0.0, tPos - dy*0.5), QPointF(myWidth + 5.0, tPos + dy*0.5) ) );
        }
    }
}


void ColourMap::annotate()
{
    qreal dt = (myMax - myMin) / myTicks;
    QString string;
    //qDebug() << "annotating...";
    if( myWidth > myHeight){ // draw the colour map horizontally
        qreal dx  = myWidth / myTicks;
        //qDebug() << "tick step : " << dx;
        for( int t = 0; t <= myTicks; ++t ){
            string.setNum(t*dt);
            QGraphicsTextItem *text = new QGraphicsTextItem(string, this);
            qreal b = (text->boundingRect().height() * 2.0 )/ 1.7320508075688772;

            // commented to compile in Qt5
            //text->translate( t*dx - b, myHeight + text->boundingRect().width() );
            //text->rotate(-60.0);
        }
    }else{
        // the colour map has to be vertical
        qreal dx  = myHeight / myTicks;
        for( int t = myTicks; t > -1; --t ){
            string.setNum((myTicks-t)*dt);
            QGraphicsTextItem *text = new QGraphicsTextItem(string, this);

            // commented to compile in Qt5
            //qreal textOffset = text->boundingRect().height()*0.5;
            //text->translate(myWidth + 6.0, t*dx - textOffset );
        }
    }
}

/*
 * Different colour maps
 *
 */

const ColourLookUp sunBurnCLUT()
{
    ColourLookUp clut;
    clut.myRed   << Bound(0.0,0.0,0.0) << Bound(0.5,1.0,1.0) << Bound(1.0,1.0,1.0);
    clut.myGreen << Bound(0.0,0.0,0.0) << Bound(0.25,0.0,0.0)<< Bound(0.75,1.0,1.0) << Bound(1.0,1.0,1.0);
    clut.myBlue  << Bound(0.0,0.0,0.0) << Bound(0.5,0.0,0.0) << Bound(1.0,1.0,1.0);
    return clut;
}


const ColourLookUp uncertaintyCLUT()
{
    ColourLookUp clut;
    clut.myRed   << Bound(0.0,1.0,1.0) << Bound(0.25, 0.8, 0.8 ) << Bound(0.75, 0.6, 0.6) << Bound(1.0,0.0,0.0);
    clut.myGreen << Bound(0.0,0.0,0.0) << Bound(0.25, 0.6, 0.6)  << Bound(0.75, 0.8, 0.8) << Bound(1.0,1.0,1.0);
    clut.myBlue  << Bound(0.0,0.0,0.0) << Bound(1.0,0.0,0.0);
    return clut;
}


const ColourLookUp vslCLUT()
{
    ColourLookUp clut;
    clut.myRed   << Bound(0.00,0.0,0.0) << Bound(0.0035,1.0,1.0) << Bound(0.083,1.00,1.00) << Bound(0.16,1.0,1.0)
               << Bound(0.33,0.5,0.5) << Bound(0.6600,0.0,0.0) << Bound(1.000,0.00,0.00);
    clut.myGreen << Bound(0.00,0.0,0.0) << Bound(0.0035,1.0,1.0) << Bound(0.083,0.75,0.75) << Bound(0.16,0.0,0.0)
               << Bound(0.33,1.0,1.0) << Bound(0.6600,1.0,1.0) << Bound(1.000,0.00,0.00);
    clut.myBlue  << Bound(0.00,0.0,0.0) << Bound(0.0035,0.0,0.0) << Bound(0.083,0.50,0.50) << Bound(0.16,1.0,1.0)
               << Bound(0.33,0.5,0.5) << Bound(0.6600,1.0,1.0) << Bound(1.000,1.00,1.00);
    return clut;
}


const ColourLookUp timeCLUT()
{
    ColourLookUp clut;
    clut.myRed   << Bound(0.0, 0.894117647, 0.894117647) << Bound(0.2, 0.556862745, 0.556862745)
                 << Bound(0.4, 0.529411765, 0.529411765) << Bound(0.6, 0.890196078, 0.890196078)
                 << Bound(0.8, 0.084507042, 0.084507042) << Bound(1.0, 0.239215686, 0.23921568 );
    clut.myGreen << Bound(0.0, 0.674509804, 0.674509804) << Bound(0.2, 0.854901961, 0.854901961)
                 << Bound(0.4, 0.439215686, 0.439215686) << Bound(0.6, 0.207843137, 0.207843137)
                 << Bound(0.8, 0.823529412, 0.823529412) << Bound(1.0, 0.098039216, 0.098039216);
    clut.myBlue  << Bound(0.0, 0.674509804, 0.674509804) << Bound(0.2, 0.592156863, 0.592156863)
                 << Bound(0.4, 0.815686275, 0.815686275) << Bound(0.6, 0.207843137, 0.207843137)
                 << Bound(0.8, 0.2,         0.2        ) << Bound(1.0, 0.68627451,  0.68627451 );
    return clut;
}


const ColourLookUp metaphoricCLUT()
{
    ColourLookUp clut;
    clut.myRed   << Bound(0.0, 0.894117647, 0.894117647) << Bound(0.2, 0.556862745, 0.556862745)
                 << Bound(0.4, 0.529411765, 0.529411765) << Bound(0.6, 0.890196078, 0.890196078)
                 << Bound(0.8, 0.084507042, 0.084507042) << Bound(1.0, 0.239215686, 0.23921568 );
    clut.myGreen << Bound(0.0, 0.674509804, 0.674509804) << Bound(0.2, 0.854901961, 0.854901961)
                 << Bound(0.4, 0.439215686, 0.439215686) << Bound(0.6, 0.207843137, 0.207843137)
                 << Bound(0.8, 0.823529412, 0.823529412) << Bound(1.0, 0.098039216, 0.098039216);
    clut.myBlue  << Bound(0.0, 0.674509804, 0.674509804) << Bound(0.2, 0.592156863, 0.592156863)
                 << Bound(0.4, 0.815686275, 0.815686275) << Bound(0.6, 0.207843137, 0.207843137)
                 << Bound(0.8, 0.2,         0.2        ) << Bound(1.0, 0.68627451,  0.68627451 );

    return clut;
}



/*
 * For day metaphor of file attribute glyph
 */

const ColourLookUp dayCLUT()
{
    ColourLookUp clut;
    clut.myRed   << Bound(0.00, 0.5, 0.0) <<
                    Bound(0.25, 1.0, 1.0) <<
                    Bound(0.50, 1.0, 1.0) <<
                    Bound(0.75, 0.0, 0.0) <<
                    Bound(1.00, 0.0, 0.5);
    clut.myGreen << Bound(0.00, 0.5, 0.0) <<
                    Bound(0.25, 0.647, 0.647) <<
                    Bound(0.50, 1.0, 1.0) <<
                    Bound(0.75, 1.0, 1.0) <<
                    Bound(1.00, 0.0, 0.5);
    clut.myBlue  << Bound(0.00, 0.5, 0.0) <<
                    Bound(0.25, 0.0, 0.0) <<
                    Bound(0.50, 0.0, 0.0) <<
                    Bound(0.75, 1.0, 1.0) <<
                    Bound(1.00, 0.0, 0.5);

    return clut;
}


/*
 * For treemap file and directory
 */

const ColourLookUp treemapFCLUT()
{
    ColourLookUp clut;
    clut.myRed   << Bound(0.00, 0.0, 0.980) <<
                    Bound(1.00, 1.0, 0.0);

    clut.myGreen << Bound(0.00, 0.0, 0.502) <<
                    Bound(1.00, 0.627, 0.0);

    clut.myBlue  << Bound(0.00, 0.0, 0.447) <<
                    Bound(1.00, 0.478, 0.0);

    return clut;
}

const ColourLookUp treemapDCLUT()
{
    ColourLookUp clut;
    clut.myRed   << Bound(0.00, 0.0, 0.204) <<
                    Bound(1.00, 0.235, 0.0);

    clut.myGreen << Bound(0.00, 0.0, 0.545) <<
                    Bound(1.00, 0.702, 0.0);

    clut.myBlue  << Bound(0.00, 0.0, 0.341) <<
                    Bound(1.00, 0.443, 0.0);

    return clut;

}

