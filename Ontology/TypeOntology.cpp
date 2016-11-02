#include "TypeOntology.h"


TypeOntology::TypeOntology(const wstring &cfgFile, const wstring &databasePath, const wstring &databaseAlias) :
              Ontology(cfgFile, databasePath, databaseAlias)

{
    // Schema
    m_ntype_term        = this->createNodeType(L"TERM");
    m_nattr_term        = this->createAttribute(m_ntype_term, L"TERMNAME", String, Unique);
    m_ntype_filetype    = this->createNodeType(L"FTYPE");
    m_nattr_filetype    = this->createAttribute(m_ntype_filetype, L"TYPENAME", String, Unique);
    m_etype_term2type   = this->createEdgeType(L"TERM2FTYPE", true, true);
    m_eattr_weight      = this->createAttribute(m_etype_term2type, L"WEIGHT", Double, Basic);
}

TypeOntology::~TypeOntology()
{

}


void TypeOntology::createOntology()
{
    cout << __PRETTY_FUNCTION__ << " Creating TypeOntology." << endl;
    cout << "Possible count: " << m_wordnet->indexList.size() << endl;
    int counter = 0;

    FileTypes *fileTypes = FileTypes::instance();
    vector <string> fileCatList = fileTypes->getFileCatList();

    Value value;

        /*
         * Scan the vector of Index/s
         */
        for (vector<Index>::iterator it = m_wordnet->indexList.begin(); it != m_wordnet->indexList.end(); it++)
        {
            string lemma = it->lemma;
            if (m_wordnet->filter(lemma) || lemma.compare("astragalar") == 0 || lemma.compare("astragalus") == 0)
                continue;
            cout <<  ++counter << " \r";

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
             * Scan the vector of file type
             * Create the connected nodes and edge from source `lemma` to type.
             */
            for (unsigned i = 0; i < fileCatList.size(); ++i)
            {
                string cat = fileCatList[i];
                oid_t typeNode = this->addNode(m_ntype_filetype, m_nattr_filetype, value.SetString(stringToWString(cat)));
                this->addEdge(m_etype_term2type, m_eattr_weight, lemmaNode, typeNode, value.SetDouble(0.5));
            }

        } // End for, scan the vector of Index/s

    cout << endl;
    cout << __PRETTY_FUNCTION__ << " TypeOntology created." << endl;
}


map <string, double> TypeOntology::findNeighbors(const string &kw)
{
    #ifdef TEST_PREFORMANCE
    cout << __PRETTY_FUNCTION__ << ": " << kw << endl;
    #endif

    map<string, double> _neighbors;
    map<wstring, double> neighbors = _findNeighbors(stringToWString(kw), m_nattr_term, m_nattr_filetype, m_etype_term2type, m_eattr_weight);
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


void TypeOntology::updateNeighbors(const string &kw, map<string, double> &neighbors)
{
    cout << __PRETTY_FUNCTION__ << ": " << kw << endl;

    map<wstring, double> _neighbors;
    for (map<string, double>::iterator it = neighbors.begin(); it != neighbors.end(); ++it)
    {
        _neighbors[stringToWString((*it).first)] = (*it).second;
    }
    this->_updateNeighbors(stringToWString(kw), m_nattr_term, _neighbors, m_nattr_filetype, m_etype_term2type, m_eattr_weight);

    #if DBG_GDB
    cout << __PRETTY_FUNCTION__ << "Updated values (calling findNeighbour): " << endl;
    findNeighbors(kw);
    #endif
}


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ EXPORT FOR VIS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  */


void TypeOntology::Prepare(Graph *graph)
{
    //
}

void TypeOntology::Release()
{
    //
}


bool_t TypeOntology::GetGraph(GraphExport &ge)
{
    ge.SetLabel(L"TypeOntology");
    return true;
}

bool_t TypeOntology::GetNodeType(type_t nodeType, NodeExport &nodeExport)//int nodetype, NodeExport * ne)
{
    // default node type export:
    // - PEOPLE in RED nodes
    // - MOVIES in ORANGE nodes
    if (nodeType == m_ntype_term)
    {
        nodeExport.SetColorRGB(16711680); // red
    }
    else if (nodeType == m_ntype_filetype)
    {
        nodeExport.SetColorRGB(65535); // cyan
    }
    else
    {
        assert(false);
    }

    return true;
}


bool TypeOntology::GetEdgeType(type_t edgetype, EdgeExport &ee)
{
    // default edge type export:
    // - CAST in YELLOW lines
    // - DIRECTS in BLUE lines
    if (edgetype == m_etype_term2type)
    {
        ee.SetColorRGB(16776960); // yellow
    }
    else
    {
        assert(false);
    }
    return true;
}


bool_t TypeOntology::GetNode(oid_t nodeId, NodeExport &ne)
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
    else if (nodetype == m_ntype_filetype)
    {
        m_graph->GetAttribute(nodeId, m_nattr_filetype, v);
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

bool_t TypeOntology::GetEdge(oid_t edgeId, EdgeExport &ee)
{
    Value v;

    int nodeType = m_graph->GetObjectType(edgeId);
    if (nodeType == m_etype_term2type)
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


bool TypeOntology::EnableType(type_t type)
{
    // enable all node and edge types
    return true;
}
