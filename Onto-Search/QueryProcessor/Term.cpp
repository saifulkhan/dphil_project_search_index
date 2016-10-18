#include "Term.h"

Term::Term(Ontology* termOntology, Ontology* typeOntology, Ontology* sizeOntology, NeuralNet* neuralNet) :
           m_termOntology(termOntology), m_typeOntology(typeOntology), m_sizeOntology(sizeOntology)
{
    m_index = SE::Index::instance();
}


Term::~Term()
{

}


/*
 * 1. Expand
 * 2. History
 * 3. Index search
 * 4. Aggregate
 */
vector<FileInfoX> Term::processTerm(const string& key, const Query& query) {
    cout << __PRETTY_FUNCTION__ << "key: " << key << endl;

    m_term  = key;
    m_query = query;
    m_fileInfoxVec.clear();

    expandTerm();
    searchTerm();
    aggregateWeight();

    return m_fileInfoxVec;
}


void Term::expandTerm()
{
    m_termWeightMap.clear();
    m_typeWeightMap.clear();
    m_sizeWeightmap.clear();
    m_termWeightMap = m_termOntology->findNeighbors(m_term);
    m_typeWeightMap = m_typeOntology->findNeighbors(m_term);
    m_sizeWeightmap = m_sizeOntology->findNeighbors(m_term);
}


void Term::searchTerm() {

    cout << __PRETTY_FUNCTION__ << endl;

    m_fileInfoxVec.clear();

    // Index: first search the original term, then its associated terms.
    // search term is already there in the map.
    for ( map<string, double>::iterator it = m_termWeightMap.begin(); it != m_termWeightMap.end(); ++it) {
        string termx = (*it).first;
        cout << __PRETTY_FUNCTION__ << " Searching term: " << termx << endl;
        vector <FileInfo> tempVec = m_index->search(termx);
        cout << __PRETTY_FUNCTION__ << " Received result: " << tempVec.size() << endl;

        for (vector <FileInfo>::iterator i = tempVec.begin(); i != tempVec.end(); ++i) {
            FileInfoX fileInfoX(*i);
            fileInfoX.m_term = m_term;
            fileInfoX.m_termx = termx;
            m_fileInfoxVec.push_back(fileInfoX);
        }
    }

    cout << __PRETTY_FUNCTION__ << " Total received results: " << m_fileInfoxVec.size() << endl;


    #ifdef DBG_FILTER
    cout << "Before filter: elements= " << m_fileInfoxVec.size() << endl;
    for (itF = m_fileInfoxVec.begin(); itF != m_fileInfoxVec.end(); ++itF)
        cout << *itF << endl;
    #endif

    /*
     * Conditional filtering: type, size, date(later)
     */

    if (m_query.type().size() > 0) {
        m_fileInfoxVec.erase(std::remove_if(m_fileInfoxVec.begin(),
                                            m_fileInfoxVec.end(),
                                            [&](const FileInfoX& arg) {
                                                set<string> types = m_query.type();
                                                set<string>::iterator it = std::find(types.begin(), types.end(), arg.m_fileInfo.m_type);
                                                if (it == types.end()) {
                                                    cout << "Remove: " << arg.m_fileInfo.m_type << " ";
                                                    return true;
                                                } else {
                                                    //cout << "Dont-remove: " << *it << endl;
                                                    return false;
                                                }
                                             }),
                             m_fileInfoxVec.end());
    }

    /*
     * If any of from/to are non zero, size will be filtered
     * Otehrwise, if both are zero, size will not be filtered.
     */
    if (m_query.size().first || m_query.size().second)
    {
        m_fileInfoxVec.erase(std::remove_if(m_fileInfoxVec.begin(), m_fileInfoxVec.end(), [&](const FileInfoX& arg)
                                            {
                                                pair<uint64_t, uint64_t> sizes = m_query.size();
                                                if ( (sizes.first <= arg.m_fileInfo.m_size) && (arg.m_fileInfo.m_size <= sizes.second))
                                                {
                                                    //cout << ": dont-remove size(" << sizes.first << " <= " << arg.m_fileInfo.m_size << " <= " << sizes.second << endl;
                                                    return false;
                                                }
                                                else
                                                {
                                                    //cout << ": remove size(" << sizes.first << " <= " << arg.m_fileInfo.m_size << " <= " << sizes.second << endl;
                                                    return true;
                                                }
                                            }),
                             m_fileInfoxVec.end());

    }
    #ifdef DBG_FILTER
    cout << "After filter: elements= " << m_fileInfoxVec.size() << endl;
    for (vector <FileInfoX>::iterator i = m_fileInfoxVec.begin(); i != m_fileInfoxVec.end(); ++i)
        cout << *i << endl;
    #endif

    cout << __PRETTY_FUNCTION__ << " Returning total result (after filter): " << m_fileInfoxVec.size() << endl;

}


void Term::aggregateWeight()
{
    #ifdef TEST_PREFORMANCE
    cout << __PRETTY_FUNCTION__ << " for term: " << m_term << endl;
    #endif
    for (vector <FileInfoX>::iterator it = m_fileInfoxVec.begin(); it != m_fileInfoxVec.end(); ++it)
    {
        string termx = (*it).m_termx;
        string typex = (*it).m_typex;
        string sizex = tokenise((*it).m_sizex, " ").back();

         // Update the filevector with aggregated weight
        (*it).m_weight = 1 - (
                         (1 - m_termWeightMap[termx]) *
                         (1 - m_typeWeightMap[typex]) *
                         (1 - m_sizeWeightmap[sizex])
                        );
        #if DBG_QP
        cout << __PRETTY_FUNCTION__ << termx << ", " << typex << ", " << sizex << endl;
        cout << "Agg. Weight: " << (*it).m_weight << " ~ " << m_termWeightMap[termx] << ", " << m_typeWeightMap[typex] << ", " << m_sizeWeightmap[sizex] << endl;
        #endif
    }
}


void Term::processFeedback(vector<FileInfoX>& newFileInfoVec)
{
    cout << __PRETTY_FUNCTION__ << " for term: " << m_term << endl;

    ReleVanceFeedback rf(newFileInfoVec);
    map<string, int> termMap = rf.termMap();
    map<string, int> typeMap = rf.typeMap();
    map<string, int> sizeMap = rf.sizeMap();

    NeuralNet neuralNet;

    map<string, int>::iterator it1;
    for (it1 = termMap.begin(); it1 != termMap.end(); ++it1)
    {
        cout << "Training: " << it1->first << " : ";
        string termx            = it1->first;
        double oldWeight        = m_termWeightMap[termx];
        m_termWeightMap[termx]  = neuralNet.train(oldWeight, it1->second);

        cout << " After tarining weight(" << termx << ") " << oldWeight << "->" << m_termWeightMap[termx] << endl;
    }

    for (it1 = typeMap.begin(); it1 != typeMap.end(); ++it1)
    {
        cout << "Training: " << it1->first << " : ";
        string typex            = it1->first;
        double oldWeight        = m_typeWeightMap[typex];
        m_typeWeightMap[typex]  = neuralNet.train(oldWeight, it1->second);

        cout << " After tarining weight(" << typex << ") " << oldWeight << "->" << m_typeWeightMap[typex] << endl;
    }

    for (it1 = sizeMap.begin(); it1 != sizeMap.end(); ++it1)
    {
        cout << "Training: " << it1->first << " : ";
        string sizex            = it1->first;
        double oldWeight        = m_sizeWeightmap[sizex];
        m_sizeWeightmap[sizex]  = neuralNet.train(oldWeight, it1->second);

        cout << " After tarining weight(" << sizex << ") " << oldWeight << "->" << m_sizeWeightmap[sizex] << endl;
    }

    cout << __PRETTY_FUNCTION__ << " Precision & recall measure. " << m_term << endl;

    m_termOntology->updateNeighbors(m_term, m_termWeightMap);
    m_typeOntology->updateNeighbors(m_term, m_typeWeightMap);
    m_sizeOntology->updateNeighbors(m_term, m_sizeWeightmap);
}
