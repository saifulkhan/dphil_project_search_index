#ifndef COLOURMAP_H
#define COLOURMAP_H

#include <QtCore>
#include <QColor>
#include <QVector>
#include <QGraphicsItem>
#include <QPainter>
#include <QPen>
#include <QWidget>

template <typename Type>
qreal linear(Type u, Type v, qreal alpha)
{
    return static_cast<qreal> ( u * (1.0 - alpha) + v * alpha);
}

struct Bound
{
  qreal value, from, to;
  Bound() : value(0.0), from(0.0), to(1.0){}

  Bound(qreal v, qreal f, qreal t) : value(v), from(f), to(t) {}

  bool operator<(const Bound &other)
  {
      return value < other.value;
  }

  bool operator>(const Bound &other)
  {
      return value > other.value;
  }

  bool operator==(const Bound &other)
  {
      return value == other.value;
  }

};


struct ColourLookUp
{
    QVector<Bound> myRed;
    QVector<Bound> myGreen;
    QVector<Bound> myBlue;

    void clear()
    {
        myRed.clear(); myGreen.clear(); myBlue.clear();
    }

    qreal red  (qreal value) const
    {
        return getColour(myRed,   value);
    }

    qreal green(qreal value) const
    {
        return getColour(myGreen, value);
    }

    qreal blue (qreal value) const
    {
        return getColour(myBlue,  value);
    }

    const QColor lookup(qreal value) const
    {
        QColor colour256;
        colour256.setRgbF (red (value), green(value), blue (value));
        return colour256;
    }

    qreal getColour(QVector<Bound> const &channel, qreal value) const
    {
        int i = 0;
        while( value > channel[i+1].value)
            ++i;

        qreal alpha = (value - channel[i].value) / qAbs (channel[i+1].value - channel[i].value);
        qreal interp = linear(channel[i].to, channel[i+1].from, alpha);
        return interp;
    }
};


class ColourMap : public QGraphicsItem
{

    Q_INTERFACES(QGraphicsItem)

private:

    qreal myWidth, myHeight, myMin, myMax, mySpan;
    int   myTicks;
    ColourLookUp myCLUT;

public:

    ColourMap(ColourLookUp clut, qreal w, qreal h,
              qreal min = 0, qreal max = 100, qreal tick= 10, QGraphicsItem *parent = 0);
    ~ColourMap();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void annotate();
    const QColor lookup (qreal value);
    const QColor lookupRGB (qreal, qreal, qreal);
    const QColor lookupHSV (qreal, qreal, qreal);
};


const ColourLookUp sunBurnCLUT();
const ColourLookUp uncertaintyCLUT();
const ColourLookUp vslCLUT();
const ColourLookUp timeCLUT();
const ColourLookUp metaphoricCLUT();
const ColourLookUp dayCLUT();
const ColourLookUp treemapFCLUT();
const ColourLookUp treemapDCLUT();


#endif // COLOURMAP_H
