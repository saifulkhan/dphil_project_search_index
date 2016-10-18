#ifndef CAUCHY_H
#define CAUCHY_H

#include "AbstractContDist.h"

class Cauchy : public AbstractContDist
{
private:
    const double m_mean;
    const double m_sd;
    cauchy_distribution <double> m_distribution;

public:
    Cauchy(const double &m, const double &s);
    int64_t generate();
};

#endif // CAUCHY_H
