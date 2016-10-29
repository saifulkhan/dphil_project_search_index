#include "Random.h"

template <class T>
T randomNo(const T &min, const T &max)
{
    static bool first = true;
    if ( first )
    {
        srand(time(NULL)); //seeding for the first time only!
        first = false;
     }
     return min + rand() % (max - min);

}


RandInt::RandInt ()
{
    srand(time(NULL));
}


RandInt::~RandInt ()
{

}

/**
 * Input is a range (min - max) and output is a random number (x) lies between (min - max).
 **/

int RandInt::getRandInt (int low, int high)
{
    if (low > high)
    {
        cout << __PRETTY_FUNCTION__ << "Fatal Error: low = high, " <<  low << " = " << high;
        return EXIT_FAILURE;
    }
    return rand() % ((high + 1) - low) + low;
}

/**
 * Bucket of elements: 0, 1, 2, 3, ..., (totalElements - 1), each appear "totalTrials" times.
 * Each element can be drawn maximum "totalTrials" times. Therefore, total number of possible draw is (totalTrials * totalElements)
 * Everytime ask for a number it wil give a random number between 0 to n - 1.
 **/

RandDraw::RandDraw (int t, int e) : totalTrials (t), totalElements (e)
{
    // initialize
    cout << __PRETTY_FUNCTION__ << "Initialize: Elements= " <<  totalElements << ", " << "Trials: " << totalTrials << endl;
    for (int i = 0; i < totalElements; i ++)
    {
        bucket.push_back (pair <int, int> (i, 0) );
    }

    randInt = new RandInt ();
}

RandDraw::~RandDraw ()
{

}

int RandDraw::draw ()
{
    // TODO: is there are anyway to avoid this scenario?
    // Application which call it should take care of this.
    if (bucket.empty())
    {
       // cout << __PRETTY_FUNCTION__ << "Empty bucket." << endl ;
        return -1;
    }

    int randIndex = randInt->getRandInt (0, (bucket.size() - 1));
    int no = bucket[randIndex].first;

    // cout << __PRETTY_FUNCTION__ << "BucketSize= " << bucket.size() << " Index(Rand)= " << randIndex << " Drawn=" << no << endl;

    if (++ bucket[randIndex].second == totalTrials)
    {
        bucket.erase(bucket.begin() + randIndex);
        // cout << __PRETTY_FUNCTION__ << "Removing: " << randIndex << endl;
    }

    return no;
}
