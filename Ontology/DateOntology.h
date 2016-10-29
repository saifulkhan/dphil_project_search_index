#ifndef WNONTOLOGY_H
#define WNONTOLOGY_H

#include <vector>
#include <assert.h>
#include "gdb/Export.h"

#include "Ontology.h"
#include "WN/Wordnet.h"

using namespace std;
using namespace WN;

class WNOntology : public Ontology, private ExportManager
{
private:
    // TERM
    type_t m_ntype_term;
    attr_t m_nattr_lemma;
    attr_t m_nattr_pos;          // part-of-speech
    attr_t m_nattr_synset_cnt;
    // EDGE
    type_t m_etype_term2term;
    attr_t m_eattr_pointer_symbol; // The relation pointer_symbol
    attr_t m_eattr_pos;
    attr_t m_eattr_weight;

    Wordnet *m_wordnet;

protected:
    bool filter(const string lemma);

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

public:
    WNOntology(const wstring &cfgFile, const wstring &databasePath, const wstring &databaseAlias);
    ~WNOntology();
    virtual void createOntology();
    virtual map <string, double> findNeighbors(const string&);
    virtual void updateNeighbors(const string&, map<string, double>&);
    virtual map <string, double> traversealDFS(const string &kw, const int &hops);


};

#endif // WNOntology_H

