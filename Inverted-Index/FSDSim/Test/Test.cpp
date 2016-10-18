#include <iostream>

#include "GenSystemStat.h"
#include "GenSimFiles.h"
#include "Distributions/TimeDistribution.h"
#include "Distributions/LogNormal.h"

using namespace std;

void test_distributions();
int help();

int main(int argc, char* argv[])
{
    #ifdef TEST_DIST
    test_distributions();
    return 0;
    #endif

    /*
     * Actual dataset generation or statistics generation code
     */
    if (argc != 3)
    {
        help();
    }
    else if (strcmp(argv[1], "GenSimFiles") == 0)
    {
        if (atoi(argv[2]))
        {
            cout << __PRETTY_FUNCTION__ << " Generating total files: " << atoi(argv[2]) << endl;
            GenSimFiles(atoi(argv[2]));
        }
    }
    else if (strcmp(argv[1], "GenSystemStat") == 0)
    {
        GenSystemStat(string(argv[2]));
    }
    return 0;
}

int help()
{
    std::cerr << "Usage: " << "./DataManager GenSimFiles <num_of_files> > <output.csv> (OR) GenSystemStat <path>" << std::endl;
    return EXIT_FAILURE;
}


/*
 * Test the distributions.
 */
void test_distributions()
{
    TimeDistribution timeDistribution;
    for (int i = 0; i < 10; ++i)
    {
        cout << timeDistribution.generate() << endl;
    }

    return;

    /// Weibul
    //Weibull dist(0.54405, 2.5418E+5);
    /// LogNormal
    LogNormal dist(9.1686, 1.5931);

    for (int i = 0; i < 1000; ++i)
    {
        int64_t number = dist.generate();
        cout << number << endl;
    }
}
