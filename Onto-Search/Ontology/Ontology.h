#ifndef ONTOLOGY_H
#define ONTOLOGY_H

#include <iostream>
#include <fstream>

#include <gdb/Sparksee.h>
#include <gdb/Database.h>
#include <gdb/Session.h>
#include <gdb/Graph.h>
#include <gdb/Objects.h>
#include <gdb/ObjectsIterator.h>
#include <gdb/Export.h>
#include <algorithms/TraversalDFS.h>

#include <Conversion.h>
#include <Wordnet.h>

using namespace WN;
using namespace std;
using namespace sparksee::gdb;
using namespace sparksee::algorithms;

class Ontology
{
protected:
    wstring m_cfgFile;
    wstring m_databasePath;
    wstring m_databaseAlias;

    Sparksee *m_sparksee;
    Database *m_database;
    Session *m_session;
    Graph *m_graph;
    Wordnet* m_wordnet;

protected:
    // Schema
    type_t createNodeType(const wstring &ntype);
    type_t createEdgeType(const wstring &etype, const bool_t &directed, const bool_t &neighbors);
    attr_t createAttribute(const type_t &type, const wstring &attrName, const DataType &dataType, const AttributeKind &attrKind);

    // Node / Edge operations
    oid_t addNode(const type_t &ntype, const attr_t &nattr, Value &value);
    oid_t addEdge(const type_t &etype, const attr_t &eattr, const oid_t &tail_nid, const oid_t &head_nid, Value &value);
    void updateAttribute(const oid_t &objId, const attr_t &attr, Value &value);

   // Search & Navigation
    map<wstring, double>
    _findNeighbors(const wstring &name, const attr_t &src_nattr, const attr_t &neighbour_nattr, const type_t &etype, const attr_t &eattr);

    map<oid_t, oid_t>
    findNeighborsID(const wstring &name, const attr_t &src_nattr, const type_t &etype);

    void _updateNeighbors(const wstring &name, const attr_t &src_nattr, map<wstring, double> &neighbors, const attr_t &neighbour_nattr, const type_t &etype, const attr_t &eattr);

    //map <wstring, double>
    //traversealDFS(const wstring &name,  const int &hops, const attr_t &nattr, const type_t &ntype, const type_t &etype, const attr_t &eattr);

public:
    // Construction
    Ontology(const wstring &cfgFile, const wstring &databasePath, const wstring &databaseAlias);
    virtual ~Ontology();

    // Implemented in derived classes; these are the methods can be called from the object.
    virtual void createOntology() = 0;
    virtual map <string, double> findNeighbors(const string&) = 0;
    virtual void updateNeighbors(const string&, map<string, double>&) = 0;
};

#endif // ONTOLOGY_H
