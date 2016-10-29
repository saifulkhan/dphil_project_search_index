#ifndef GENSIMFILES_H
#define GENSIMFILES_H

#include <map>
#include <iostream>
#include <stdexcept>
#include <fstream>

#include "Distributions/ContDistFactory.h"
#include "Distributions/DiscreteDist.h"
#include "Distributions/TimeDistribution.h"
#include <FileTypes.h>
#include "Namespace.h"
#include "Conversion.h"

using namespace std;

class GenSimFiles
{
    unsigned              m_numFiles;
    map <string, string>  m_typeCategoryMap;
    static vector<string> m_dns;
    Namespace             m_namespace;
    ofstream              m_datafile;
    DiscreteDist          m_discreteDist;
    DiscreteDist*         m_typeDist;
    DiscreteDist*         m_nameDist;
    DiscreteDist*         m_userDist;
    DiscreteDist*         m_groupDist;
    TimeDistribution      m_timeDistribution;

    string  baseName();
    int64_t size(const string& type);
    string  path();
    void    constructPath(NodeXml* parent, string* str);


public:
    GenSimFiles(unsigned numFiles);
    ~GenSimFiles();
    void generateFiles(const uint64_t& id);
};

#endif // GENSIMFILES_H
