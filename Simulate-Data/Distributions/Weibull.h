#ifndef WEIBULL_H
#define WEIBULL_H

#include "AbstractContDist.h"

class Weibull : public AbstractContDist
{
private:
    const double m_a;
    const double m_b;
    weibull_distribution <double> m_distribution;

public:
    Weibull(const double &alpha, const double &beta);
    int64_t generate();
};

#endif // WEIBULL_H

