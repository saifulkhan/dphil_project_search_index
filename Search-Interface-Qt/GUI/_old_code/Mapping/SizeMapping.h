#ifndef SIZEMAP_H
#define SIZEMAP_H


#include <QtCore>
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


struct SizeLookUp
{
    QVector<Bound> band;

    void clear()
    {
        band.clear();
    }

    qreal lookup(qreal value) const
    {
        int i = 0;
        while( value > band[i+1].value )
            ++i;

        qreal alpha = (value - band[i].value) / qAbs (band[i+1].value - band[i].value);
        qreal interp = linear(band[i].to, band[i+1].from, alpha);
        return interp;
    }
};



class SizeMap
{
private:

public:
    SizeMap();


};

#endif // SIZEMAP_H
