#ifndef INDEXREADER_H_
#define INDEXREADER_H_

#include <string.h>
#include <string>
#include <stdio.h>
#include <iostream>
#include <map>
#include <vector>
#include "stdHeader.h"
#include "IndexOutput.h"
#include "Document.h"
#include "HitDoc.h"
#include "IndexInput.h"

using namespace std;

class IndexReader {

public: // TODO: private (?)
    char *p_tii;
    char *p_fdi;
    char *p_fdt;
    char *p_fmn;
    char *p_pro;
    char *p_del;
    char *path;
    char *indexName;
    string segName;
    string m_strPath;
    std::int64_t docCount;
    std::int64_t delCount;
    std::int64_t termCount;
    IndexInput *p_tiiInput;
    IndexInput *p_fdiInput;
    IndexInput *p_fdtInput;
    IndexInput *p_fmnInput;
    IndexInput *p_proInput;
    IndexInput *p_delInput;
    IndexOutput *p_delOutput;
    Document m_doc;
    map<string, std::int64_t> m_termMap;
    map<std::int64_t, std::int64_t > m_delMap;

private:
    void loadFmn();
    void loadTerm();
    void loadDel();
    string getSegName();

public:
    IndexReader();
    IndexReader(char* indexPath);
    std::int64_t getNumDoc();
    std::int64_t  getTermCount();
    vector<HitDoc> getTermDocs(string &term);
    void getTermDocs(string &term, vector<HitDoc> &docVo);
    void doc(std::int64_t docId, Document & doc);
    void del(std::int64_t docId);
    void open(char* indexPath);
	virtual ~IndexReader();
};

#endif /*INDEXREADER_H_*/
