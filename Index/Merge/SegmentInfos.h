#ifndef SEGMENTINFOS_H_
#define SEGMENTINFOS_H_

#include <string.h>
#include <string>
#include <stdio.h>
#include <iostream>
#include <map>
#include "stdHeader.h"
#include "IndexOutput.h"
#include "IndexInput.h"
#include "Document.h"

using namespace std;

struct Segment
{
    std::int64_t startNum;
    std::int64_t docCount;
    string segName;
};


class SegmentInfos
{
public:
    map <string, Segment> m_segMap;
    std::int64_t m_docCount;
    string nextSegName;
	char *p_segment;

public:
    SegmentInfos();
    virtual ~SegmentInfos();
    void load( char *path );
    string getNextSegName();
};

#endif /*SEGMENTINFOS_H_*/
