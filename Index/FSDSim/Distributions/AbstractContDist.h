#ifndef ABSTRACTCONTDIST_H
#define ABSTRACTCONTDIST_H


#include <iostream>
#include <vector>
#include <random>
#include <functional>
#include <sstream>
#include <fstream>
#include <cassert>

#include <ctime>
#include <ratio>
#include <chrono>

using namespace std;
using namespace std::chrono;

class AbstractContDist
{
protected:
    mt19937_64 m_rng;

public:
    AbstractContDist();
    virtual ~AbstractContDist() {}
    virtual int64_t generate() = 0;
};

#endif // ABSTRACTDIST_H
