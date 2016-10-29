#ifndef LOGNORMAL_H
#define LOGNORMAL_H

#include "AbstractContDist.h"

class LogNormal : public AbstractContDist
{
private:
    const double m_mean;
    const double m_sd;
    lognormal_distribution <double> m_distribution;

public:
    LogNormal(const double &mean, const double &sd);
    int64_t generate();
};

#endif // LOGNORMAL_H
