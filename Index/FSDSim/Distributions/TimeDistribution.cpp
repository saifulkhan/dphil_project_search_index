#include "TimeDistribution.h"

TimeDistribution::TimeDistribution()
{
    m_distribution = uniform_int_distribution<int> (0, MAX_NUM_OF_SECONDS);
    m_now_seconds  = (unsigned int)time(NULL);

}

string TimeDistribution::generate()
{
    unsigned int rand_seconds = m_distribution(m_generator);
    time_t rand_time          = (time_t)(m_now_seconds - rand_seconds);
    struct tm* ptm            = localtime(&rand_time);

    /*
     *  Qt::ISODate format
     */

    char buffer[80];
    strftime(buffer, 80, "%Y-%m-%dT%H:%M:%S", ptm);        // YYYY-MM-DDTHH:mm:ss

    string datetime(buffer);
    return datetime;
}
