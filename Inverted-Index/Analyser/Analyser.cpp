#include "Analyser.h"

void searchInIndexTime()
{
    string line;
    string label;
    vector <string> queries;

    // TODO: Change it
    ifstream fs("/mnt/DATA/Dropbox/DPhil-Research/Data/Stat/TestTerms.csv");
    if (!fs.is_open())
    {
        cerr << __PRETTY_FUNCTION__ << " Does not exist, check.";
        return;
    }
    while (getline(fs, line))
    {
        stringstream ss(line);
        getline(ss, label, ',');
        //ss >> value;

        queries.push_back(label);
    }
    fs.close();

    cout << __PRETTY_FUNCTION__ << " Search time (ms):" << endl;

    for(vector <string>::iterator it = queries.begin(); it != queries.end(); ++it)
    {
        Stopwatch<> sw;

        //functionToBeTimed(arg1, arg2);


        sw.stop();
        std::cout << "functionToBeTimed took " << sw.elapsed() << " microseconds\n";

    }

}

