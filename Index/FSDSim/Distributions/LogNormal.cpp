#include "LogNormal.h"

LogNormal::LogNormal(const double &mean, const double &sd) :
    m_mean(mean), m_sd(sd)
{

    m_distribution = lognormal_distribution <double> (m_mean, m_sd);
}

int64_t LogNormal::generate()
{
    int64_t number = m_distribution(m_rng);
    return number;
}
