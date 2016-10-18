#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <map>
#include <utility>

using namespace std;

template <class T> T randomNo(const T &min, const T &max);

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ CLASSES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class RandInt
{
    private:

    public:
        RandInt ();
        ~RandInt ();
        int getRandInt (int low, int high);
};


class RandDraw
{
    private:
        const int totalTrials;
        const int totalElements;
        vector <pair <int, int> > bucket;
        RandInt *randInt;

    public:
        RandDraw (int totalTrials, int totalElements);
        ~RandDraw ();
        int draw ();

};
