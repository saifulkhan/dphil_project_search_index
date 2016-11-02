#ifndef TYPEONTOLOGY_H
#define TYPEONTOLOGY_H

#include <vector>
#include <assert.h>
#include <gdb/Export.h>
#include "Ontology.h"
#include "FileTypes.h"

// This is a guessed value : Sparksee trial version only support limited number of nodes.
// In case license is vailable comment the section of code in the cpp file.
# define MAX_COUNT 150000 

using namespace std;

class TypeOntology : public Ontology, private ExportManager
{
private:
    type_t m_ntype_term;        // TERM
    attr_t m_nattr_term;
    type_t m_ntype_filetype;    // FTYPE
    attr_t m_nattr_filetype;
    type_t m_etype_term2type;   // Edge between term and ftype
    attr_t m_eattr_weight;

public:
    TypeOntology(const wstring &cfgFile, const wstring &databasePath, const wstring &databaseAlias);
    ~TypeOntology();
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

#endif // TYPEONTOLOGY_H

