#ifndef SIZEONTOLOGY_H
#define SIZEONTOLOGY_H

#include <vector>
#include <assert.h>
#include <gdb/Export.h>
#include "Ontology.h"
#include "FileTypes.h"

using namespace std;

class SizeOntology : public Ontology, private ExportManager
{
private:
    type_t m_ntype_term;        // TERM
    attr_t m_nattr_term;
    type_t m_ntype_filesize;    // FTYPE
    attr_t m_nattr_filesize;
    type_t m_etype_term2size;   // Edge between term and ftype
    attr_t m_eattr_weight;

public:
    SizeOntology(const wstring &cfgFile, const wstring &databasePath, const wstring &databaseAlias);
    ~SizeOntology();
    virtual void createOntology();
    virtual map <string, double> findNeighbors(const string&);
    virtual void updateNeighbors(const string&, map<string, double>&);

private:
    // Export related
    void Prepare(Graph *graph);
    void Release();
    bool_t GetGraph(GraphExport &graphExport);
    bool_t GetNodeType(type_t type, NodeExport &nodeExport);
    bool_t GetEdgeType(type_t type, EdgeExport &edgeExport);
    bool_t GetNode(oid_t node, NodeExport &nodeExport);
    bool_t GetEdge(oid_t edge, EdgeExport &edgeExport);
    bool_t EnableType(type_t type);
    // end of export related
};

#endif // SIZEONTOLOGY_H

