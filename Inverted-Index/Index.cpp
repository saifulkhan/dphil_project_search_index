#include "Index.h"

namespace SE {

    Index* Index::m_cache = NULL;

    Index* Index::instance() {
        if (!m_cache)
            m_cache = new Index();
        return m_cache;
    }

    Index::Index() {
        m_cachePath = DIR_CACHE_PATH;
        cout << __PRETTY_FUNCTION__ << " Index location: " << m_cachePath << endl;        
    }


    Index::~Index() {

    }


    /*
     *  Index::open() and Index::close() should be closed when
     *  - Index is built, modified or updated.
     */

    void Index::open() {
        m_indexWriter = new IndexWriter();
        m_indexWriter->open(m_cachePath.c_str(), true ); // TODO: must end with "/", else crashes.
        m_indexWriter->setBufferDoc(2);

        //m_indexSearch = new IndexSearch();
        //m_indexSearch->open((char *) m_cachePath.c_str());
    }


    void Index::close() {
        m_indexWriter->close();
        //delete m_indexSearch;
    }

    /*
     * TODO - can we optimise the string of int64_t
     */
    void Index::add(const FileInfo& fileInfo)
    {
        Field *field0 = new Field(STORE_STRING, STORE_YES, STORE_NO_TOKEN, "docId",        int64ToString(fileInfo.m_docId));
        Field *field1 = new Field(STORE_STRING, STORE_YES, STORE_KEYWORD,  "fileName",     fileInfo.m_fileName);
        Field *field2 = new Field(STORE_STRING, STORE_YES, STORE_KEYWORD,  "type",         fileInfo.m_type);
        //Field *field3 = new Field(STORE_LONG, STORE_YES, STORE_KEYWORD, "size",         sizeStr);
        Field *field3 = new Field(STORE_STRING, STORE_YES, STORE_NO_TOKEN, "size",         int64ToString(fileInfo.m_size));
        Field *field4 = new Field(STORE_STRING, STORE_YES, STORE_NO_TOKEN, "lastModified", fileInfo.m_lastModified);
        Field *field5 = new Field(STORE_STRING, STORE_YES, STORE_NO_TOKEN, "lastRead",     fileInfo.m_lastRead);
        Field *field6 = new Field(STORE_STRING, STORE_YES, STORE_NO_TOKEN, "created",      fileInfo.m_created);
        Field *field7 = new Field(STORE_STRING, STORE_YES, STORE_NO_TOKEN, "user",        fileInfo.m_user);
        Field *field8 = new Field(STORE_STRING, STORE_YES, STORE_NO_TOKEN, "group",        fileInfo.m_group);
        Field *field9 = new Field(STORE_STRING, STORE_YES, STORE_NO_TOKEN, "path",         fileInfo.m_path);

        // Add fields
        Document doc;
        doc.addField("docId",    field0);
        doc.addField("fileName", field1);
        doc.addField("type",     field2);
        doc.addField("size",     field3);
        doc.addField("lastModified", field4);
        doc.addField("lastRead", field5);
        doc.addField("created",  field6);
        doc.addField("user",    field7);
        doc.addField("group",    field8);
        doc.addField("path",     field9);

        m_indexWriter->addDocument(doc);

        #ifdef DBG_CACHE
        cout << __PRETTY_FUNCTION__ << fileInfo << endl;
        #endif
    }


    vector <FileInfo> Index::search(const string& term) {

        vector <FileInfo> result;
        vector<HitDoc> hitVo;

        IndexSearch indexSearch;
        indexSearch.open((char *) m_cachePath.c_str());
        indexSearch.SearchTerm(term, hitVo);

        cout << __PRETTY_FUNCTION__ << " Searched term: " << term << ", hits: " << indexSearch.hitCounts << endl;

        for(int i = 0; i < indexSearch.hitCounts; i++) {
            HitDoc  hdoc = hitVo[i];
            Document doc;
            int64_t id = hdoc.getDocId();

            indexSearch.doc(id, doc);

            #ifdef DBG_CACHE
            cout << "id= " << id << ", hits= " << hdoc.getHits() << endl;
            cout << "  fileName= "      <<  doc.getStringField("fileName")
                 << ", type= "          << doc.getStringField("type")
                 << ", size= "          << doc.getLongField("size")
                 << ", lastModified= "  << doc.getStringField("lastModified")
                 << ", path= "          << doc.getStringField("path")
                 << endl;
             #endif

            FileInfo fileInfo(stringToInt64(doc.getStringField("docId")),
                              doc.getStringField("fileName"),
                              doc.getStringField("type"),
                              stringToInt64(doc.getStringField("size")),
                              doc.getStringField("lastModified"),
                              doc.getStringField("lastRead"),
                              doc.getStringField("created"),
                              doc.getStringField("user"),
                              doc.getStringField("group"),
                              doc.getStringField("path"));

            result.push_back(fileInfo);

            #ifdef DBG_CACHE
            cout << __PRETTY_FUNCTION__ << fileInfo << endl;
            #endif

        }

        cout << __PRETTY_FUNCTION__ << " Returning total results: " << result.size() << endl;
        return result;
    }


    /*
     * A debug function, reads the entire cache.
     */
    vector <FileInfo> Index::read()
    {
        cout << __PRETTY_FUNCTION__ << endl;
        vector <FileInfo> fileInfoVec;

        IndexReader *indexReader = new IndexReader();
        indexReader->open((char*) m_cachePath.c_str());

        for (int i = 0; i < indexReader->getNumDoc(); i++)
        {
            Document doc;
            indexReader->doc(i, doc);

            FileInfo fileInfo(stringToInt64(doc.getStringField("docId")),
                              doc.getStringField("fileName"),
                              doc.getStringField("type"),
                              stringToInt64(doc.getStringField("size")),
                              doc.getStringField("lastModified"),
                              doc.getStringField("lastRead"),
                              doc.getStringField("created"),
                              doc.getStringField("user"),
                              doc.getStringField("group"),
                              doc.getStringField("path"));

            fileInfoVec.push_back(fileInfo);
        }

        cout << __PRETTY_FUNCTION__ << ": Index size: " << indexReader->getNumDoc() << endl;

        delete indexReader;
        return fileInfoVec;
    }

} // endof namespace SE
