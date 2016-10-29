#include "QueryProcessor.h"

QueryProcessor::QueryProcessor() {
    m_queryParser  = new QueryParser();
    m_treemap = new Treemap();

    m_termOntology = OntologyFactory::createConnection("TermOntology");
    m_typeOntology = OntologyFactory::createConnection("TypeOntology");
    m_sizeOntology = OntologyFactory::createConnection("SizeOntology");
    m_neuralNet    = new NeuralNet;
}


QueryProcessor::~QueryProcessor() {
    delete m_treemap;
    delete m_queryParser;

    delete m_termOntology;
    delete m_typeOntology;
    delete m_sizeOntology;
    delete m_neuralNet;

    for (vector<Term*>::iterator i = m_termVec.begin(); i != m_termVec.end(); ++i) {
        if (i != m_termVec.end())
            break;
        delete *i;
    }
}

/***************************************************************************************************************
 * Public methods: Treemap
 ***************************************************************************************************************/

string QueryProcessor::treemap(const int x, const int y, const int width, const int height) {
    string jsonstring = m_treemap->treemap(x, y, width, height);
    return jsonstring;
}

string QueryProcessor::treemap(const int depth) {
    string jsonstring = m_treemap->treemap(depth);
    return jsonstring;
}

/***************************************************************************************************************
 * Public methods: Search
 ***************************************************************************************************************/

string QueryProcessor::search(const string &query) {
    cout << __PRETTY_FUNCTION__ << query << endl;
    this->processQuery(query);

    json_spirit::Array array = this->toJSONObject(m_result);

    //DBG: Write to file, for debugging or using while developing w/o angular.
#ifdef DBG_QP
    ofstream os;
    os.open("result.json");
    json_spirit::write(array, os, json_spirit::pretty_print);
    os.close();
#endif

    string jsonstr =  json_spirit::write(array);
    return jsonstr;
}


/*************************************************************************************************************************
 * Feedback
 *************************************************************************************************************************/
void QueryProcessor::feedback(const string& feedback) {
    cout << "QueryProcessor::feedback: " << feedback << endl;
    //m_term->processFeedback(newFileInfoVec);
}

void QueryProcessor::saveSession() {
    cout << "QueryProcessor::saveSession: " << endl;

}


/*************************************************************************************************************************
 * Public Methods: Search Qt standalone code
 *************************************************************************************************************************/

vector<FileInfoX> QueryProcessor::searchQtStandalone(const string &query)
{
    this->processQuery(query);
    return m_result;
}

void QueryProcessor::feedbackQtStandalone()
{

}



/*************************************************************************************************************************
 * Private methods: to do query processing and training
 * Parse the query.
 * Process all the terms.
 **************************************************************************************************************************/

void QueryProcessor::processQuery(const string &query)
{
   cout << __PRETTY_FUNCTION__ << endl;

    m_query = m_queryParser->parse(query);
    set<string> keys = m_query.key();
    m_result.clear();

    vector<FileInfoX> intersection;
    for (set<string>::const_iterator i = keys.begin(); i != keys.end(); ++i)
    {
        cout << __PRETTY_FUNCTION__ << *i << endl;
        if (i == keys.end())
           break;

        Term* term = new Term(m_termOntology, m_typeOntology, m_sizeOntology, m_neuralNet);
        vector<FileInfoX> result = term->processTerm(*i, m_query);

        /*
         * Sort received result by doc id.
         */
        sort(result.begin(), result.end(),
             [](const FileInfoX& arg1, const FileInfoX& arg2)
            {
                 return (arg1.m_fileInfo.m_docId < arg2.m_fileInfo.m_docId);
            });

        /*
         * Intersect (by id) all the results for: term1, term2, ...
         */

        if (m_result.empty())
        {
            m_result = result;
        }
        else
        {
            #ifdef DBG_FILTER
            cout << *i << endl;
            cout << "=====result======: " << endl;
            for (vector <FileInfoX>::iterator itemp = result.begin(); itemp != result.end(); ++itemp)
                cout << *itemp << endl;

            cout << "=====m_result=====: " << endl;
            for (vector <FileInfoX>::iterator itemp = m_result.begin(); itemp != m_result.end(); ++itemp)
                cout << *itemp << endl;
            #endif

            intersection.clear();
            set_intersection(result.begin(), result.end(), m_result.begin(), m_result.end(), back_inserter(intersection),
                             [](const FileInfoX& arg1, const FileInfoX& arg2)
                             {
                                return (arg1.m_fileInfo.m_docId < arg2.m_fileInfo.m_docId);
                             });

            m_result.clear();
            m_result = intersection;

            #ifdef DBG_FILTER
            cout << "=====intersection======" << endl;
            for (vector <FileInfoX>::iterator itemp = intersection.begin(); itemp != intersection.end(); ++itemp)
                cout << *itemp << endl;
            #endif
        }

        //m_termVec.push_back(term);
    }

    for (vector <FileInfoX>::iterator itemp = m_result.begin(); itemp != m_result.end(); ++itemp)
        cout << *itemp << endl;

    //sort
    std::sort(m_result.begin(), m_result.end(),
            [](const FileInfoX& arg1, const FileInfoX& arg2)
            {
                return (arg1.m_weight < arg2.m_weight);
            });
}

/*
 * Convert the result into json objects
 */
json_spirit::Array QueryProcessor::toJSONObject(vector<FileInfoX> result)
{
    json_spirit::Array array;

    for(vector<FileInfoX>::iterator it = result.begin(); it != result.end(); ++it)
    {
        FileInfoX fileInfoX = *it;

        json_spirit::Object obj;
        obj.push_back(json_spirit::Pair("docid",  fileInfoX.m_fileInfo.m_docId));
        obj.push_back(json_spirit::Pair("select", fileInfoX.m_select));
        obj.push_back(json_spirit::Pair("weight", fileInfoX.m_weight));
        obj.push_back(json_spirit::Pair("name",   fileInfoX.m_fileInfo.m_fileName));
        obj.push_back(json_spirit::Pair("type",   fileInfoX.m_typex));
        obj.push_back(json_spirit::Pair("size",   fileInfoX.m_sizex));
        obj.push_back(json_spirit::Pair("date",   fileInfoX.m_fileInfo.m_lastModified));
        obj.push_back(json_spirit::Pair("age",    fileInfoX.m_agex));
        obj.push_back(json_spirit::Pair("user",   fileInfoX.m_fileInfo.m_user));
        obj.push_back(json_spirit::Pair("group",  fileInfoX.m_fileInfo.m_group));

        string fileFullPath = fileInfoX.m_fileInfo.m_path + "/" + fileInfoX.m_fileInfo.m_fileName;
        RectF rectF = m_treemap->coordinate(fileFullPath);

        obj.push_back(json_spirit::Pair("x", rectF.x()));
        obj.push_back(json_spirit::Pair("y", rectF.y()));

        array.push_back(obj);
    }
    return array;
}
