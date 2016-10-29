#include "Weibull.h"

Weibull::Weibull(const double &a, const double &b) :
    m_a(a), m_b(b)
{
    m_distribution = weibull_distribution <double> (m_a, m_b);
}

int64_t Weibull::generate()
{
    int64_t number = m_distribution(m_rng);
    return number;
}
