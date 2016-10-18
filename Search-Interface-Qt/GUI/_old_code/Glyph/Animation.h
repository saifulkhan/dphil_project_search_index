#ifndef ANIMATION_H
#define ANIMATION_H

#include <QtCore>
#include <QObject>
#include <QColor>
#include <vector>

using namespace std;

class Animation : public QObject
{
    Q_OBJECT
    Q_ENUMS (AnimationType)

public:
    enum AnimationType {null, opacity, blink, fade, scale, rotationX, rotationY, rotationZ, shutter};

    AnimationType antype;
    double start;
    double stop;
    double duration;
    unsigned points;
    QVector <QPair <double, double> > tfVector;

    // Methods
    Animation (AnimationType antype = null, double start = 0, double stop = 0, double duration = 0,
                QVector <QPair <double, double> >  tfVector = QVector <QPair <double, double> >  () );

    Animation &operator= (const Animation &);
    Animation (const Animation &);
    friend  QDebug operator<< (QDebug, const Animation &);

    void setType (QString);
    QString getTypeString () const;

};

#endif // ANIMATION_H
