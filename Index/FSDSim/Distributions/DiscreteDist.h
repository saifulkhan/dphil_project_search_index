#ifndef DISCRETEDIST_H
#define DISCRETEDIST_H

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

using namespace  std;

class DiscreteDist
{
private:
    mt19937_64 m_rng;

    vector<string> m_elementVec;
    vector<int> m_weightVec;
    discrete_distribution <int> m_distribution;

    void readFile(const string &file);

public:
    DiscreteDist();
    DiscreteDist(const string &file);
    DiscreteDist(vector<string>& elementVec);
    ~DiscreteDist();
    string generate();

    void initialise(vector<string> element, vector<int> weight);
    void pmf();
};

#endif // DISCRETEDIST_H
