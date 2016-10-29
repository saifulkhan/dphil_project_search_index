#include "Ontology.h"


Ontology::Ontology(const wstring &cfgFile, const wstring &databasePath, const wstring &databaseAlias)
{
    m_cfgFile = cfgFile;
    m_databasePath = databasePath;
    m_databaseAlias = databaseAlias;
    m_wordnet = Wordnet::instance();

    ifstream ifile(wstringToString(m_cfgFile).c_str());
    if (!ifile)
    {
        cout << __PRETTY_FUNCTION__ << wstringToString(m_cfgFile) << ": does not exist. Abort!";
        abort();
    }
    else
        cout << __PRETTY_FUNCTION__ << "Configuration: " << wstringToString(m_cfgFile) << endl;

    /*
     * Intialize the Configuration
     */
    SparkseeProperties::Load(m_cfgFile);
    SparkseeConfig cfg;
    //cfg.SetRecoveryEnabled(true);
    m_sparksee = new Sparksee(cfg);



    /*
     * Open Database
     */
    ifstream ifile1(wstringToString(m_databasePath).c_str());
    if (ifile1)
    {
        cout << __PRETTY_FUNCTION__  << wstringToString(m_databasePath) << ": exists. Opening it..." << endl;
        try
        {
            m_database = m_sparksee->Open(databasePath, false);
        }
        catch (const sparksee::gdb::FileNotFoundException &ex)
        {
            cout << __PRETTY_FUNCTION__ << "dex::gdb::FileNotFoundException: " << wstringToString(m_databasePath) << endl;
        }
        catch (const sparksee::gdb::Error &ex)
        {
            cout << __PRETTY_FUNCTION__ << "dex::gdb::Error" << endl;
        }
    }
    else
    {
        cout << __PRETTY_FUNCTION__  << wstringToString(m_databasePath) << ": doesn't exist. Creating it..." << endl;
        m_database = m_sparksee->Create(m_databasePath, m_databaseAlias);
    }

    /*
     * Open session
     */
    m_session = m_database->NewSession();
    m_graph = m_session->GetGraph();
}


Ontology::~Ontology()
{
    cout << __PRETTY_FUNCTION__ << wstringToString(m_databaseAlias) << " Exporting and closing, wait." << endl;

    ExportManager * expMngr = new DefaultExport();
    //m_graph->Export(m_databaseAlias, Graphviz, expMngr); // Juat naming as alias
    delete expMngr;

    /*
     * Close the database
     */
    delete m_session;
    delete m_database;
    delete m_sparksee;
    cout << __PRETTY_FUNCTION__ << wstringToString(m_databaseAlias) << " Closed." << endl;
}


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ SCHEMA ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  */

/*
 * Check if the node type (string) exists,
 * If doesn't exist then create a new node type,
 * Else return the existing type id
 */
type_t Ontology::createNodeType(const wstring &ntype)
{
    type_t typeId = m_graph->FindType(ntype);
    if (Type::InvalidType == typeId)
	{
        #ifdef DBG_GDB
        cout << __PRETTY_FUNCTION__  << wstringToString(ntype) << " doesn't exist, create a new node type." << endl;
        #endif
        typeId = m_graph->NewNodeType(ntype);
    } 
    else
	{
        #ifdef DBG_GDB
        wcout << __PRETTY_FUNCTION__  << "Found a existing node type. ";
        #endif
    }

    #ifdef DBG_GDB
    Type *tdata = m_graph->GetType(typeId);
    cout << "Node type `" << wstringToString(tdata->GetName()) << "` with " << tdata->GetNumObjects() << " objects." << endl;
    delete tdata;
    #endif

    return typeId;
}


/*
 * Same as above, `createNodeType` method, but it is for edge.
 */
type_t Ontology::createEdgeType(const wstring &etype, const bool_t &directed, const bool_t &neighbors)
{
    type_t typeId = m_graph->FindType(etype);
    if (Type::InvalidType == typeId)
    {
        #ifdef DBG_GDB
        cout << __PRETTY_FUNCTION__  << wstringToString(etype) << " doesn't exist, create a new edge type." << endl;
        #endif
        typeId = m_graph->NewEdgeType(etype, directed, neighbors);
    }
    else
    {
        #ifdef DBG_GDB
        wcout << __PRETTY_FUNCTION__  << "Found a existing edge type. ";
        #endif
    }

    #ifdef DBG_GDB
    Type *tdata = m_graph->GetType(typeId);
    cout << "Edge type `" << wstringToString(tdata->GetName()) << "` with " << tdata->GetNumObjects() << " objects." << endl;
    delete tdata;
    #endif

    return typeId;
}


/*
 * Find if the attribute of a node/edge type typeId exists,
 * If does not exist create a new attribute for typeId,
 * Else return the existing one
 */
attr_t Ontology::createAttribute(const type_t &typeId, const wstring &attrName, const DataType &dataType, const AttributeKind &attrKind)
{
    attr_t attrType = m_graph->FindAttribute(typeId, attrName);
    if (Attribute::InvalidAttribute == attrType) 
	{
        #ifdef DBG_GDB
        cout << __PRETTY_FUNCTION__  << "Create a new attribute: " ;
        #endif
        attrType = m_graph->NewAttribute(typeId, attrName, dataType, attrKind);
    } 
	else 
	{
        #ifdef DBG_GDB
        cout << "Found a existing attribute of the given node/edge type." << endl;
        #endif
    }

    #ifdef DBG_GDB
    Attribute *adata = m_graph->GetAttribute(attrType);
    Type *tdata = m_graph->GetType(typeId);
    cout << "Attribute `" << wstringToString(adata->GetName()) << "` of node/edge type `" << wstringToString(tdata->GetName()) << "` created." << endl;
    delete tdata;
    delete adata;
    #endif

    return attrType;
}


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ADD / UPDATE ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  */

/*
 * Checks is node exists first
 * If doesnot exist then create
 *
 * Every node is identified with a unique attribute/value of a node.
 * FindObject() method finds if there any node exist with that attribute value.
 */
oid_t Ontology::addNode(const type_t &ntype, const attr_t &nattr, Value &value)
{
    // Check if a node exists with similar attribute value (this is unique id / name)
    oid_t nid = m_graph->FindObject(nattr, value);
    if ( nid == Objects::InvalidOID)
    {
        #ifdef DBG_GDB
        cout << __PRETTY_FUNCTION__ << "Create a new node object." << endl;
        #endif
        nid = m_graph->NewNode(ntype);
        m_graph->SetAttribute(nid, nattr, value);
    }

    return nid;
}


/*
 * Check edge exists, else create and update the attribute value
 */
oid_t Ontology::addEdge(const type_t &etype, const attr_t &eattr, const oid_t &tailnid, const oid_t &headnid, Value &value)
{
    // Check if a similar type of edge exists between the tail and head nodes
    oid_t eid = m_graph->FindEdge(etype, tailnid, headnid);
    if (eid == Objects::InvalidOID)
    {
        #ifdef DBG_GDB
        cout << __PRETTY_FUNCTION__ << "Create a new edge (tailnid, headnid): ";
        #endif
        eid = m_graph->NewEdge(etype, tailnid, headnid);
        m_graph->SetAttribute(eid, eattr, value);

    }

    #ifdef DBG_GDB
    cout << tailnid << ", " << headnid << endl;
    #endif
    return eid;
}


/*
 * Used to update an attribute of a node/edge
 * The node/edge id is: objId
 */
void Ontology::updateAttribute(const oid_t &objId, const attr_t &attr, Value &value)
{
    m_graph->SetAttribute(objId, attr, value);
    #ifdef DBG_GDB
    cout << __PRETTY_FUNCTION__ << "Updated the attributes." << endl;
    #endif
}




/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ SARCH & NAVIGATION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  */

/*
 * Find neighbours of a node: its attribute and name given
 * The node Returns the <name, edge-weight> map of all the neighbour nodes.
 */
map <wstring, double>
Ontology::_findNeighbors(const wstring &name, const attr_t &src_nattr, const attr_t &neighbour_nattr, const type_t &etype, const attr_t &eattr)
{
    map <wstring, double> neighbors;
    Value *value = NULL;

    map <oid_t, oid_t> neighborid = findNeighborsID(name, src_nattr, etype);
    for (map <oid_t, oid_t>::iterator it = neighborid.begin(); it != neighborid.end(); ++it)
    {
        value = m_graph->GetAttribute((*it).first, neighbour_nattr);  // Neighbor node attribute
        wstring neighbor = value->GetString();
        value = m_graph->GetAttribute((*it).second, eattr);           // The corresponding edge attribute/weight
        double weight = value->GetDouble();

        neighbors[neighbor] = weight;
    }
    delete value;

    return neighbors;
}


/*
 * Find the neighbour of a node.
 * The node Returns the <node_id, edge_id> map of all the neighbours.
 */
map <oid_t, oid_t>
Ontology::findNeighborsID(const wstring &name, const attr_t &src_nattr, const type_t &etype)
{
    map <oid_t, oid_t> neighbors;
    Value value;
    value.SetString(name);

    oid_t src_nid = m_graph->FindObject(src_nattr, value);                  // find the source node id first
    if (src_nid != Objects::InvalidOID)
    {
        Objects *objs = m_graph->Neighbors(src_nid, etype, Outgoing);   // find the connected neighbour nodes
        ObjectsIterator * it = objs->Iterator();

        while (it->HasNext())
        {
            oid_t neighbor_nid = it->Next();                                      // Neighbor node id
            oid_t neighbor_eid = m_graph->FindEdge(etype, src_nid, neighbor_nid); // the corresponding edge id
            neighbors[neighbor_nid] = neighbor_eid;
        }
        delete objs;
        delete it;
    }
    return neighbors;
}


/*
 * Source node is given, update its neighbour connections
 *
 */
void Ontology::_updateNeighbors(const wstring &name, const attr_t &src_nattr, map<wstring, double> &neighbors, const attr_t &neighbour_nattr, const type_t &etype, const attr_t &eattr)
{

    Value *value = NULL;
    map <oid_t, oid_t>:: iterator it;
    map <wstring, double>::iterator itx;

    map <oid_t, oid_t> neighborid = findNeighborsID(name, src_nattr, etype);                            // find all the neighbours first
    for (it = neighborid.begin(); it != neighborid.end(); ++it)                                         // iterate the neighbours one-by-one
    {
        value = m_graph->GetAttribute((*it).first, neighbour_nattr);                                    // get the neighbor node attribute's value/name
        wstring str = value->GetString();

        itx = neighbors.find(str);                                                                      // find the new weight of that node
        if (itx != neighbors.end())
        {
            m_graph->SetAttribute((*it).second, eattr, value->SetDouble(neighbors.find(str)->second));  // change the weight of the connection
        }
     }

    delete value;
}


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ OTHER  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  */



/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ NOT USED  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  */


#if 0

map <wstring, double>
Ontology::traversealDFS(const wstring &name, const int &hops, const attr_t &nattr, const type_t &ntype, const type_t &etype, const attr_t &eattr)
{
    cout << __PRETTY_FUNCTION__ << " Started." << endl;
    Value value;
    value.SetString(name);
    oid_t src_nid = m_graph->FindObject(nattr, value);; // source node identifier

    TraversalDFS dfs(*m_session, src_nid);
    dfs.AddAllEdgeTypes(Outgoing);
    dfs.AddNodeType(ntype);
    dfs.SetMaximumHops(hops);
    while (dfs.HasNext())
    {
        cout << "Current node " << dfs.Next() << " at depth " << dfs.GetCurrentDepth() << endl;
    }

    cout << __PRETTY_FUNCTION__ << " Complete." << endl;

}



/*
 * Find more than one edge between the tail and head nodes, use the Edges() method
 * This will work if the edge type is undirected or if you just want to find an edge FROM tailnid TO headnid,
 * but this methods will not find directed  edges in the "wrong" direction.
 */

oid_t Ontology::findEdges(const type_t &edgeType, const oid_t &tailnid, const oid_t &headnid)
{
    Objects *edges =  m_graph-> Edges(edgeType, tailnid, headnid);
    ObjectsIterator *it = edges->Iterator();
    while (it->HasNext())
    {
        edgeId = it->Next();
        // Edge found
    }
    delete it;
    delete edges;

    // Once you have found the identifier of the edge, you can update the edge attribute like this:

    // You just have to set the "Value" object using the method that matches the type of the edge attribute you are using.
    // In the example, the edgeAttribute was created as an INTEGER, so the "SetInteger()" method is used to set the value.
    // That's valid for any attribute type, including String, but not for the long TEXT attributes. The TEXT attributes are
    // different because they can be too big to be set with just one call (see the user manual).

    Value *value;
    value = m_graph->GetAttribute(edgeId, edgeAttribute);
    if ( value->IsNull() )
    {
        value->SetInteger(0);
    }
    else
    {
        value->SetInteger(value->GetInteger()+1);
    }
    m_graph->SetAttribute(edgeId, edgeAttribute, *value);
    delete value;
}
#endif
