#ifndef NAMESPACE_H
#define NAMESPACE_H

#include <QtXml>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <map>

using namespace std;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ NodeXml Structure ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

struct NodeXml
{
public:
    string type;
    string name;
    unsigned weight;
    unsigned depth;
    list <NodeXml*> children;

    NodeXml(string type, string name, unsigned weight, unsigned depth);
    ~NodeXml();
    void deleteNode(NodeXml* node);
    void print(NodeXml* node);

};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ XML Reader ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

class Namespace
{
    NodeXml *m_rootNode;

    void parseXML(const string& xmlFile);
    void parseRegion(QXmlStreamReader& xml, NodeXml* parent);
    void parseLocation(QXmlStreamReader& xml, NodeXml* parent);
    void parseSector(QXmlStreamReader& xml, NodeXml* parent);
    void parseFileSystem(QXmlStreamReader& xml, NodeXml* parent);

public:
    Namespace();
    ~Namespace();
    NodeXml* rootNode() const { return m_rootNode; }
};

#endif // NAMESPACE_H
