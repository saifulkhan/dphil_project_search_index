#ifndef TIMEDISTRIBUTION_H
#define TIMEDISTRIBUTION_H

#include <iostream>
#include <time.h>
#include <random>
#include <sstream>

#define MAX_NUM_OF_SECONDS (5 * 365 * 24 * 60 * 60) // Number of seconds in 5 years

using namespace std;

class TimeDistribution
{
private:
    default_random_engine           m_generator;
    uniform_int_distribution<int>   m_distribution;
    unsigned int                    m_now_seconds;

public:
    TimeDistribution();
    string generate();
};

#endif // TIMEDISTRIBUTION_H
