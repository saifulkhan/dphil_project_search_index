#include "DiscreteDist.h"


DiscreteDist::DiscreteDist()
{
}

DiscreteDist::~DiscreteDist()
{

}

/*
 *  We can initialise/re-initialise it later on, if we are constructing it withouit any input/default ctor..
 */
void DiscreteDist::initialise(vector<string> element, vector<int> weight)
{
    assert(element.size() == weight.size());
    m_elementVec = element;
    m_weightVec = weight;

    m_distribution = discrete_distribution <int> (m_weightVec.begin(), m_weightVec.end());
}

/*
 *  Distribution will be created by reading a file, with format: ITEM WEIGHT
 */
DiscreteDist::DiscreteDist(const string &file)
{
    this->readFile(file);
    m_distribution = discrete_distribution <int> (m_weightVec.begin(), m_weightVec.end());
}


/*
 * Distribution can be created from a list of items.
 * Here prob. of all items are equal, as freq/weight is not given.
 */
DiscreteDist::DiscreteDist(vector<string>& elementVec)
{
    for (string str : elementVec)
    {
        m_elementVec.push_back(str);
        m_weightVec.push_back(1);
    }
    m_distribution = discrete_distribution <int> (m_weightVec.begin(), m_weightVec.end());
}


string DiscreteDist::generate()
{
    int number = m_distribution(m_rng);
    return m_elementVec[number];
}

void DiscreteDist::pmf()
{
    cout << "PMF: " << endl;
    int i = 0;
    for (double x : m_distribution.probabilities())
        cout << ++i << ": " << string(x * 100, '*') << endl;
}


/*
 * Reading a input file, the format of the input file is: ITEM(label) WEIGHT(value)
 */
void DiscreteDist::readFile(const string &file)
{
    string line;
    string label;
    int value;

    ifstream fs(file);
    if (!fs.is_open())
    {
        cerr << __PRETTY_FUNCTION__ << file << " Does not exist, check.";
        return;
    }
    while (getline(fs, line))
    {
        stringstream ss(line);
        getline(ss, label, ',');
        ss >> value;

        m_elementVec.push_back(label);
        m_weightVec.push_back(value);
    }
    fs.close();
    assert(m_elementVec.size() == m_weightVec.size());

    #if DEBUG
    for (int i = 0; i < m_elementVec.size(); ++i)
       cout << m_elementVec[i] << " " << m_weightVec[i] << endl;
    #endif
}



/*
string DiscreteDist::generate(high_resolution_clock::time_point t0)
{
    high_resolution_clock::duration d = high_resolution_clock::now() - t0;
    m_rng.seed(d.count());

    int number = m_distribution(m_rng);
    return m_elementVec[number];
}
*/
