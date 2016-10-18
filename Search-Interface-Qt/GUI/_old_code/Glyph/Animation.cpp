#include "Animation.h"


Animation::Animation (AnimationType antype, double start, double stop, double duration,
              QVector <QPair <double, double> >  tfVector)
{
    this->antype = antype;
    this->start = start;
    this->stop = stop;
    this->duration = duration;

    this->points = tfVector.size();
    this->tfVector = tfVector;
}


Animation& Animation::operator= (const Animation &p)
{
    this->antype = p.antype;
    this->start = p.start;
    this->stop = p.stop;
    this->duration = p.duration;

    this->points = p.points;
    this->tfVector.clear();
    this->tfVector = p.tfVector;

    return *this;
}


Animation::Animation (const Animation &p)
{
    this->antype = p.antype;
    this->start = p.start;
    this->stop = p.stop;
    this->duration = p.duration;

    this->points = p.points;
    this->tfVector = p.tfVector;
}


void Animation::setType (QString str)
{
    int index = metaObject ()->indexOfEnumerator ("AnimationType");
    QMetaEnum metaEnum = metaObject () ->enumerator (index);
    antype = (AnimationType) metaEnum.keyToValue (str.toLatin1());
}


QString Animation::getTypeString () const
{
    int index = metaObject()->indexOfEnumerator ("AnimationType");
    QMetaEnum metaEnum = metaObject()->enumerator (index);
    return metaEnum.valueToKey (antype);
}


QDebug operator<< (QDebug debug, const Animation &an)
{
    debug.nospace() << "Animation: "
                    << "Type = " << an.getTypeString () << ", "
                    << "Start-Stop = " << an.start << "-" << an.stop << ", "
                    << "Duration = " << an.duration << ", "
                    << "TF = " ;
     for (unsigned i = 0; i < an.tfVector.size(); i++)
        debug.nospace() << "(" << an.tfVector[i].first << "," << an.tfVector[i].second << ") ";

     return debug.space();
}
