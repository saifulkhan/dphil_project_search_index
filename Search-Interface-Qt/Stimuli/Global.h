#ifndef TF_H
#define TF_H

#include <QVector>
#include <QPair>
#include <QImage>
#include <QtDebug>
#include <QFile>
#include <QTextStream>
#include <QGraphicsScene>


namespace Stimuli
{
    #define TRAINING_TRIAL  1
    #define TEST_TRIAL 10

    // Trnafer Function related
    #define TOTAL_TF 15
    typedef QPair <double, double> PAIR;
    typedef QVector <PAIR > VECTOR;
    VECTOR getTF (int index);

    // White noise delay
    #define WN_DELAY 500 //msec

    extern QString id;
}
#endif // TF_H
