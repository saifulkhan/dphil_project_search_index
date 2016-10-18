#ifndef GENSYSTEMSTAT_H
#define GENSYSTEMSTAT_H

#include <fstream>
#include <FileInfo.h>
#include <FileTypes.h>


//#include "Crawler.h"
//#include "Configuration.h"

class GenSystemStat
{
    vector <FileInfo> m_fileInfoVec;
    map<string, string> m_typeCategoryMap;

    void nameStat();
    void typeStat();
    void sizeStat();

public:
    GenSystemStat();
    ~GenSystemStat() { }
};

#endif // GENSYSTEMSTAT_H
