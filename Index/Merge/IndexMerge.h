#ifndef INDEXMERGE_H_
#define INDEXMERGE_H_

#include "SegmentInfos.h"

using namespace std;

class IndexMerge
{
private:
	SegmentInfos m_segmentInfos;
    string m_path;
    Document m_doc;

    void loadfmn();
    void copyDoc(IndexOutput &destFdt,IndexInput &input);
    void loadTii(IndexInput &tiiInput, map< string, map< string, std::int64_t> > &termMap, string segName);
    void loadDel(IndexInput &delInput, map< string, vector< std::int64_t>  > &delMap, string segName);
    void removeOldIndex();

public:
	IndexMerge();
	IndexMerge(char *path);
	virtual ~IndexMerge();
	void  open(char *path);
	void merge();
};

#endif /*INDEXMERGE_H_*/
