/*
 * TODO:
 * read () -> readSearchSpace()
 *  	add the treemap functionalities or search space here
 * search() -> searchTerm
 *
 */

#ifndef CACHE_H
#define CACHE_H

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include <FileInfo.h>
#include <Conversion.h>

#include "IndexSearch.h"
#include "IndexWriter.h"
#include "IndexReader.h"

using namespace std;

namespace SE {

    class Index
    {
    private:
        string       m_cachePath;
        string       m_crawlDiskPath;
        IndexWriter* m_indexWriter;
        IndexSearch *m_indexSearch;

    private:
        // Singleton
        static Index* m_cache;
        Index();
        Index(Index const&) { }
        // Index& operator=(Index const&) { } // TODO: Commented for

    public:
        static Index* instance();
        ~Index();
        void open();
        void close();
        void add(const FileInfo& fileInfo);
        vector <FileInfo> search(const string& term);
        vector <FileInfo> read();
    };
}
#endif // CACHE_H
