#include "SizeOntology.h"


SizeOntology::SizeOntology(const wstring &cfgFile, const wstring &databasePath, const wstring &databaseAlias) :
              Ontology(cfgFile, databasePath, databaseAlias)

{
    // Schema
    m_ntype_term        = this->createNodeType(L"TERM");
    m_nattr_term        = this->createAttribute(m_ntype_term, L"TERMNAME", String, Unique);
    m_ntype_filesize    = this->createNodeType(L"SIZE");
    m_nattr_filesize    = this->createAttribute(m_ntype_filesize, L"SIZENAME", String, Unique);
    m_etype_term2size   = this->createEdgeType(L"TERM2SIZE", true, true);
    m_eattr_weight      = this->createAttribute(m_etype_term2size, L"WEIGHT", Double, Basic);
}

SizeOntology::~SizeOntology()
{

}


void SizeOntology::createOntology()
{
    cout << __PRETTY_FUNCTION__ << " Creating SizeOntology." << endl;
    cout << "Possible count: " << m_wordnet->indexList.size() << endl;
    int counter = 0;

    vector <string> sizeList = {"B", "KB", "MB", "GB", "TB", "PB", "EB", "ZB"};
    Value value;

       /*
        * Scan the vector of Index/s in wordnet
        */
        for (vector<Index>::iterator it = m_wordnet->indexList.begin(); it != m_wordnet->indexList.end(); it++)
        {
            string lemma = it->lemma;
            if (m_wordnet->filter(lemma))
                continue;
 
            cout <<  ++counter << " %\r";
 
            // In case license is vailable comment this.
            if(counter > MAX_COUNT) {
                break;
            }

            #ifdef DBG_GDB
            cout << "Create node: " << lemma << endl;
            #endif
            /*
            * create node, and a directed-edge of type pos to the below words/nodes
            */
            oid_t lemmaNode = this->addNode(m_ntype_term, m_nattr_term, value.SetString(stringToWString(lemma)));
            /*
            * Scan the vector of file size
            * Create the connected nodes and edge from source `lemma` to type.
            */
            for (unsigned i = 0; i < sizeList.size(); ++i)
            {
                string size = sizeList[i];
                oid_t sizeNode = this->addNode(m_ntype_filesize, m_nattr_filesize, value.SetString(stringToWString(size)));
                this->addEdge(m_etype_term2size, m_eattr_weight, lemmaNode, sizeNode, value.SetDouble(0.5));
            }

            // } // if-temp

        } // End for, scan the vector of Index/s


    cout << endl;
    cout << __PRETTY_FUNCTION__ << " SizeOntology created." << endl;
}


map <string, double> SizeOntology::findNeighbors(const string &kw)
{
    #ifdef TEST_PREFORMANCE
    cout << __PRETTY_FUNCTION__ << ": " << kw << endl;
    #endif

    map<string, double> _neighbors;
    map<wstring, double> neighbors = _findNeighbors(stringToWString(kw), m_nattr_term, m_nattr_filesize, m_etype_term2size, m_eattr_weight);
    #ifdef TEST_PREFORMANCE
    if (neighbors.size() == 0)
        cout << __PRETTY_FUNCTION__ << "No neighbour/similar nodes found in the ontology graph." <<  endl;
    #endif
    // Change wstring to string
    for (map<wstring, double>::iterator it = neighbors.begin(); it != neighbors.end(); ++it)
    {
        #if DBG_GDB
        cout << "kw= " << wstringToString((*it).first) << ", weight= " <<  (*it).second << endl;
        #endif
        _neighbors[wstringToString((*it).first)] = (*it).second;
    }

    return _neighbors;
}


void SizeOntology::updateNeighbors(const string &kw, map<string, double> &neighbors)
{
    cout << __PRETTY_FUNCTION__ << ": " << kw << endl;

    map<wstring, double> _neighbors;
    for (map<string, double>::iterator it = neighbors.begin(); it != neighbors.end(); ++it)
    {
        _neighbors[stringToWString((*it).first)] = (*it).second;
    }
    this->_updateNeighbors(stringToWString(kw), m_nattr_term, _neighbors, m_nattr_filesize, m_etype_term2size, m_eattr_weight);

    #if DBG_GDB
    cout << __PRETTY_FUNCTION__ << "Updated values (calling findNeighbour): " << endl;
    findNeighbors(kw);
    #endif
}


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ EXPORT FOR VIS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  */


void SizeOntology::Prepare(Graph *graph)
{
    //
}

void SizeOntology::Release()
{
    //
}


bool_t SizeOntology::GetGraph(GraphExport &ge)
{
    ge.SetLabel(L"SizeOntology");
    return true;
}

bool_t SizeOntology::GetNodeType(type_t nodeType, NodeExport &nodeExport)//int nodetype, NodeExport * ne)
{
    // default node type export:
    // - PEOPLE in RED nodes
    // - MOVIES in ORANGE nodes
    if (nodeType == m_ntype_term)
    {
        nodeExport.SetColorRGB(16711680); // red
    }
    else if (nodeType == m_ntype_filesize)
    {
        nodeExport.SetColorRGB(65535); // cyan
    }
    else
    {
        assert(false);
    }

    return true;
}


bool SizeOntology::GetEdgeType(type_t edgetype, EdgeExport &ee)
{
    // default edge type export:
    // - CAST in YELLOW lines
    // - DIRECTS in BLUE lines
    if (edgetype == m_etype_term2size)
    {
        ee.SetColorRGB(16776960); // yellow
    }
    else
    {
        assert(false);
    }
    return true;
}


bool_t SizeOntology::GetNode(oid_t nodeId, NodeExport &ne)
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
    else if (nodetype == m_ntype_filesize)
    {
        m_graph->GetAttribute(nodeId, m_nattr_filesize, v);
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

bool_t SizeOntology::GetEdge(oid_t edgeId, EdgeExport &ee)
{
    Value v;

    int nodeType = m_graph->GetObjectType(edgeId);
    if (nodeType == m_etype_term2size)
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


bool SizeOntology::EnableType(type_t type)
{
    // enable all node and edge types
    return true;
}
