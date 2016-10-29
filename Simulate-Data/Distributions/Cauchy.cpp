#include "Cauchy.h"

Cauchy::Cauchy(const double &mean, const double &sd) :
    m_mean(mean), m_sd(sd)
{
    m_distribution = cauchy_distribution<double> (m_mean, m_sd);
}

int64_t Cauchy::generate()
{
    int64_t number = m_distribution(m_rng);
    return number;
}
