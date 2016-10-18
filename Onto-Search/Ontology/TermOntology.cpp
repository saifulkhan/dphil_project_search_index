#include "TermOntology.h"


TermOntology::TermOntology(const wstring &cfgFile, const wstring &databasePath, const wstring &databaseAlias) :
            Ontology(cfgFile, databasePath, databaseAlias)
{
    // Schema
    m_ntype_term        = this->createNodeType(L"TERM");
    m_nattr_term        = this->createAttribute(m_ntype_term, L"TERMNAME", String, Unique);
    //m_nattr_pos        = this->createAttribute(m_ntype_term, L"POS", String, Basic);
    //m_nattr_synset_cnt = this->createAttribute(m_ntype_term, L"SYNSETCNT", Integer, Basic);

    m_etype_term2term   = this->createEdgeType(L"TERM2TERM", true, true);
    m_eattr_weight      = this->createAttribute(m_etype_term2term, L"WEIGHT", Double, Basic);
    m_eattr_pos         = this->createAttribute(m_etype_term2term, L"POS", String, Basic);
    //m_eattr_pointer_symbol   = this->createAttribute(m_etype_term2term, L"WEIGHT", Double, Basic);
}


TermOntology::~TermOntology()
{

}


void TermOntology::createOntology()
{
    cout << __PRETTY_FUNCTION__ << " Creating TermOntology." << endl;
    cout << "Possible count: " << m_wordnet->indexList.size() * (POS_ARRAY_SIZE - 1) << endl;
    int counter = 0;
    Value value;

    for (unsigned p = 1; p <= POS_ARRAY_SIZE - 1; p++)
    { //a
        /*
         * Scan the vector of Index/s
         */
        for ( vector<Index>::iterator it = m_wordnet->indexList.begin(); it != m_wordnet->indexList.end(); it++)
        {
            string lemma = it->lemma;
            string posStr = get_pos_from_enum(it->pos);
            if (m_wordnet->filter(lemma))
                continue;
            cout <<  ++counter << " %\r";

            #ifdef DBG_GDB
            cout << "Create node: lemma/pos= " << lemma << "/" << posStr << endl;
            #endif
            /*
             * create node, and a directed-edge of type pos to the below words/nodes
             */
            oid_t lemmaNode = this->addNode(m_ntype_term, m_nattr_term, value.SetString(stringToWString(lemma)));
            /*
             * Scan the vector of synset_offsets
             */
            for (unsigned i = 0; i < it->synset_offsets.size(); i++)
            {
                int offset = it->synset_offsets[i];
                pos_t pos = it->pos;
                if (pos == (pos_t)p)
                { //d
                    int u = m_wordnet->info.compute_indice(offset, pos);
                    vector<string> words = m_wordnet->offsetWordList[u];
                    /*
                     * Create the connected nodes and edge from source `lemma`.
                     */
                    for (unsigned k = 0; k < words.size(); ++k)
                    {
                        string word = words[k];
                        oid_t wordNode = this->addNode(m_ntype_term, m_nattr_term, value.SetString(stringToWString(word)));
                        this->addEdge(m_etype_term2term, m_eattr_weight, lemmaNode, wordNode, value.SetDouble(0.5));
                     }
                } //d
            } // End, scan the vector of synset_offsets
        } // End, scan the vector of Index/s
    } //a
    cout << endl;
    cout << __PRETTY_FUNCTION__ << " TermOntology created." << endl;
}


map <string, double> TermOntology::findNeighbors(const string &kw)
{
    #ifdef TEST_PREFORMANCE
    cout << __PRETTY_FUNCTION__ << ": " << kw << endl;
    #endif

    map<string, double> _neighbors;
    map<wstring, double> neighbors = this->_findNeighbors(stringToWString(kw), m_nattr_term, m_nattr_term, m_etype_term2term, m_eattr_weight);;
    #ifdef TEST_PREFORMANCE
    if (neighbors.size() == 0)
        cout << __PRETTY_FUNCTION__ << "No neighbour/similar nodes found in the ontology graph." <<  endl;
    #endif
    for (map<wstring, double>::iterator it = neighbors.begin(); it != neighbors.end(); ++it)
    {
        #if DBG_GDB
        cout << "kw= " << wstringToString((*it).first) << ", weight= " <<  (*it).second << endl;
        #endif
        _neighbors[wstringToString((*it).first)] = (*it).second;
    }

    return _neighbors;
}

void TermOntology::updateNeighbors(const string &kw, map<string, double> &neighbors)
{
    cout << __PRETTY_FUNCTION__ << ": " << kw << endl;

    map<wstring, double> _neighbors;
    for (map<string, double>::iterator it = neighbors.begin(); it != neighbors.end(); ++it)
    {
        _neighbors[stringToWString((*it).first)] = (*it).second;
    }
    this->_updateNeighbors(stringToWString(kw), m_nattr_term, _neighbors, m_nattr_term, m_etype_term2term, m_eattr_weight);

    #if DBG_GDB
    cout << __PRETTY_FUNCTION__ << "Updated values (calling findNeighbour): " << endl;
    findNeighbors(kw);
    #endif
}


map<string, double> TermOntology::traversealDFS(const string &kw, const int &hops)
{
    map<wstring, double>::iterator it;
    map<string, double> _neighbors;

    //this->_traversealDFS(stringToWString(kw), hops,  m_nattr_term, m_ntype_term, m_etype_term2term, m_eattr_weight);
/*

    if (neighbors.size() == 0)
        cout << __PRETTY_FUNCTION__ << "No neighbour/similar nodes found in wordnet." <<  endl;

    for (it = neighbors.begin(); it != neighbors.end(); ++it)
    {
        cout << __PRETTY_FUNCTION__ << "kw= " << (*it).first << ", weight= " <<  (*it).second << endl;
        _neighbors[wstringToString((*it).first)] = (*it).second;
    }

    //return _neighbors;
*/
}


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ EXPORT FOR VIS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  */


void TermOntology::Prepare(Graph *graph)
{
    //
}

void TermOntology::Release()
{
    //
}


bool_t TermOntology::GetGraph(GraphExport &ge)
{
    ge.SetLabel(L"TermOntology");
    return true;
}

bool_t TermOntology::GetNodeType(type_t nodeType, NodeExport &nodeExport)//int nodetype, NodeExport * ne)
{
    // default node type export:
    // - PEOPLE in RED nodes
    // - MOVIES in ORANGE nodes
    if (nodeType == m_ntype_term)
    {
        nodeExport.SetColorRGB(16711680); // red
    }
    else
    {
        assert(false);
    }

    return true;
}


bool TermOntology::GetEdgeType(type_t edgetype, EdgeExport &ee)
{
    // default edge type export:
    // - CAST in YELLOW lines
    // - DIRECTS in BLUE lines
    if (edgetype == m_etype_term2term)
    {
        ee.SetColorRGB(16776960); // yellow
    }
    else
    {
        assert(false);
    }
    return true;
}


bool_t TermOntology::GetNode(oid_t nodeId, NodeExport &ne)
{
    // specific node export:
    // - PEOPLE: use the Name attribute as label
    // - MOVIES: uset the Title attribute as label

    Value v;

    int nodetype = m_graph->GetObjectType(nodeId);
    if (nodetype == m_ntype_term)
    {
        m_graph->GetAttribute(nodeId, m_nattr_term, v);
    }
    else
    {
        assert(false);
    }

    std::wstring aux2;
    std::wstringstream aux;
    aux << v.ToString(aux2);
    ne.SetLabel(aux.str());
    //cout << __PRETTY_FUNCTION__ << L"[" << nodeId << L"]" << v.ToString(aux2) << endl;

    return true;

}

bool_t TermOntology::GetEdge(oid_t edgeId, EdgeExport &ee)
{
    Value v;

    int nodeType = m_graph->GetObjectType(edgeId);
    if (nodeType == m_etype_term2term)
    {
        m_graph->GetAttribute(edgeId, m_eattr_weight, v);
    }
    else
    {
        assert(false);
    }

    std::wstring aux2;
    std::wstringstream aux;
    aux << v.ToString(aux2);
    ee.SetLabel(aux.str());
    //cout << __PRETTY_FUNCTION__ << L"[" << edgeId << L"]" << v.ToString(aux2) << endl;

    return true;
}


bool TermOntology::EnableType(type_t type)
{
    // enable all node and edge types
    return true;
}
