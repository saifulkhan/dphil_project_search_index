#ifndef QUERYPROCESSOR_H
#define QUERYPROCESSOR_H

#include <iostream>
#include <vector>
#include <utility> // std::pair
#include <json_spirit_writer.h>
#include <json_spirit_value.h>

#include <FileInfo.h>

#include "Treemap.h"
#include "QueryParser.h"
#include "Term.h"

using namespace std;

class QueryProcessor {
private:
    Query           m_query;
    Treemap*        m_treemap;
    QueryParser*    m_queryParser;
    Ontology*       m_termOntology;
    Ontology*       m_typeOntology;
    Ontology*       m_sizeOntology;
    NeuralNet*      m_neuralNet;

    vector <Term*>    m_termVec;
    vector<FileInfoX> m_result;

    json_spirit::Array toJSONObject(vector<FileInfoX>);
    void processQuery(const string &);

public:
    QueryProcessor();
    ~QueryProcessor();
    string treemap(const int x, const int y, const int width, const int height);
    string treemap(const int depth);
    string search(const string& query);
    void feedback(const string& feedback);
    void saveSession();

    // Used with QtStandalone code
    vector<FileInfoX> searchQtStandalone(const string& query);
    void feedbackQtStandalone();


};

#endif // QUERYPROCESSOR_H
