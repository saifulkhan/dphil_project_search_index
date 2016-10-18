#ifndef INDEXSEARCH_H_
#define INDEXSEARCH_H_

#include <map>

#include "Tokeniser.h"
#include "IndexReader.h"
#include "PriQueue.h"

using namespace std;

class IndexSearch
{
private:
	std::string path;
	IndexReader *reader;
    Tokeniser m_tokeniser;

public:
    std::int64_t hitCounts;  // The number of documents
	
public:
	IndexSearch();
    virtual ~IndexSearch();
    void open(char * indexPath);
	void SearchTerm(std::string term,std::vector<HitDoc> &hitVo);
	void SearchAndString(std::string str,std::vector<HitDoc> &hitVo);
	void SearchOrString(std::string str,std::vector<HitDoc> &hitVo);
    void  doc(std::int64_t docId,Document & doc);
};

#endif /*INDEXSEARCH_H_*/
