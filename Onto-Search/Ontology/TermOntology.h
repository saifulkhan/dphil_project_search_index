#ifndef TERMONTOLOGY_H
#define TERMONTOLOGY_H

#include <vector>
#include <assert.h>
#include <gdb/Export.h>
#include "Ontology.h"

using namespace std;

class TermOntology : public Ontology, private ExportManager
{
private:
    // TERM
    type_t m_ntype_term;
    attr_t m_nattr_term;
    attr_t m_nattr_pos;          // part-of-speech
    attr_t m_nattr_synset_cnt;
    // EDGE
    type_t m_etype_term2term;
    attr_t m_eattr_pointer_symbol; // The relation pointer_symbol
    attr_t m_eattr_pos;
    attr_t m_eattr_weight;

public:
    TermOntology(const wstring &cfgFile, const wstring &databasePath, const wstring &databaseAlias);
    ~TermOntology();
    virtual void createOntology();
    virtual map <string, double> findNeighbors(const string&);
    virtual void updateNeighbors(const string&, map<string, double>&);
    map <string, double> traversealDFS(const string &kw, const int &hops);


protected:
    // Export related
    void Prepare(Graph *graph);
    void Release();
    bool_t GetGraph(GraphExport &graphExport);
    bool_t GetNodeType(type_t type, NodeExport &nodeExport);
    bool_t GetEdgeType(type_t type, EdgeExport &edgeExport);
    bool_t GetNode(oid_t node, NodeExport &nodeExport);
    bool_t GetEdge(oid_t edge, EdgeExport &edgeExport);
    bool_t EnableType(type_t type);
    // End of export
};

#endif // TERMONTOLOGY_H

