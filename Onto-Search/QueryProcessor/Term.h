#ifndef TERM_H
#define TERM_H

#include <iostream>
#include <vector>
#include <utility> // std::pair

#include <OntologyFactory.h>
#include <Index.h>
#include <Conversion.h>

#include "QueryParser.h"
#include "NeuralNet.h"
#include "RelevanceFeedback.h"

using namespace std;

class Term
{
private:
    string     m_term;
    Query      m_query;
    Ontology*  m_termOntology;
    Ontology*  m_typeOntology;
    Ontology*  m_sizeOntology;
    NeuralNet* m_neuralNet;
    SE::Index*     m_index;

    vector<FileInfoX>   m_fileInfoxVec;
    map<string, double> m_termWeightMap;
    map<string, double> m_typeWeightMap;
    map<string, double> m_sizeWeightmap;

    void expandTerm();
    void searchTerm();
    void aggregateWeight();

public:
    Term(Ontology*, Ontology*, Ontology*, NeuralNet*);
    ~Term();
    vector<FileInfoX> processTerm(const string& term, const Query& query);
    void              processFeedback(vector<FileInfoX>& result); // TODO it only need docid of selected docs
};

#endif
