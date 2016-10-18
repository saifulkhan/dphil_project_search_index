#ifndef INDEXWRITER_H_
#define INDEXWRITER_H_

#include <string.h>
#include <string>
#include <stdio.h>
#include <iostream>
#include <map>

#include "Tokeniser.h"
#include "stdHeader.h"
#include "IndexOutput.h"
#include "IndexInput.h"
#include "Document.h"
#include "IndexMerge.h"

using namespace std;

class IndexWriter
{
private:
    string m_strPath;
    char *path;
    bool isCreate;
    char *indexName;

    char *p_tii;        // terms and offset in .pro
    char *p_pro;        // doc# and freq of the term
    char *p_fdi;        // offset in .fdt for each document
    char *p_fdt;        // stored Field data
    char *p_fmn;        // info about Field, except Field data
    char *p_del;
    char *p_segment;
    IndexOutput *p_tiiOutput;
    IndexOutput *p_proOutput;
    IndexOutput *p_fdiOutput;
    IndexOutput *p_fdtOutput;
    IndexOutput *p_fmnOutput;
    IndexOutput *p_delOutput;
    //IndexOutput *p_segmentOutput;

    std::int64_t docCount;
    int32_t fieldCount;
    std::int64_t termCount;
    std::int64_t curBufferDoc;
    std::int64_t bufferDoc;
    Document m_doc;

    Tokeniser m_tokeniser;

    map <string, map <std::int64_t, int32_t> > m_termMap;

private:
    void initSegment( bool create );
    void loadfmn( char *fmn );
    void loadfdi( char *fdi );

    void loadsegments( map <string, int32_t> &m_segmentMap );
    void getSegName( char *name );
    void writeSegment();
    void loadtii(char *tii);


public:
	IndexWriter();
    virtual ~IndexWriter();
    void open( const char *filepath, bool create );
    void addDocument( Document &doc );
    void setBufferDoc( std::int64_t num );
    void close();
    void flush();
};

#endif /*INDEXWRITER_H_*/
