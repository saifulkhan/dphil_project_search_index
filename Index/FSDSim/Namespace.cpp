#include "Namespace.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ NodeXml Structure ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

NodeXml::NodeXml(string type, string name, unsigned weight, unsigned depth)
{
    this->type = type;
    this->name = name;
    this->weight = weight;
    this->depth = depth;
    this->children.clear();
}


NodeXml::~NodeXml()
{

}


void NodeXml::deleteNode(NodeXml* node)
{
    std::list<NodeXml*>::iterator it = node->children.begin();
    while (it != node->children.end())
    {
        NodeXml* child = *it;

        node->children.erase(it++);
        this->deleteNode(child);
    }

    #ifdef DBG_DATA
    cout << "Deleting: " << node->name << endl;
    #endif
    delete(node);
}


void NodeXml::print(NodeXml* item)
{
    cout << "NodeXml:" << item->type << ", " << item->name << ", " << item->weight
         << ", " << item->depth << ", #Children= " << item->children.size() << endl;

    foreach (NodeXml* it, item->children)
    {
        if (it->children.size() == 0)
        {
            cout << "Leaf NodeXml:" << it->type << ", " << it->name << ", " << it->weight
                 << ", " << it->depth << ", #Children= " << it->children.size() << endl;
        }
        else
        {
            print(it);
        }
    }
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Parse XML file ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

Namespace::Namespace()
{
    m_rootNode = new NodeXml("Root", "mnt", 0, 0);
    this->parseXML(FILE_LOR_ORG);

    #ifdef DBG_DATA
    m_rootNode->print(m_rootNode);
    #endif
}


Namespace::~Namespace()
{
    m_rootNode->deleteNode(m_rootNode);
}


void Namespace::parseXML(const string &xmlFile)
{
    QFile* file = new QFile(QString::fromStdString(xmlFile));
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
    {
       return;
    }
    QXmlStreamReader xml(file);
    while(!xml.atEnd() && !xml.hasError())
    {
        QXmlStreamReader::TokenType token = xml.readNext();
        if(token == QXmlStreamReader::StartDocument)
        {
            continue;
        }
        else if(token == QXmlStreamReader::StartElement)
        {
            if(xml.name() == "mnt")
                continue;

            if(xml.name() == "Region")
                this->parseRegion(xml, m_rootNode);   // Region is under mnt
        }
    }

    if(xml.hasError())
        cerr << __PRETTY_FUNCTION__ << ", " << __LINE__ << endl;

    xml.clear();
}

void Namespace::parseRegion(QXmlStreamReader &xml, NodeXml* parent)
{
    NodeXml* regionNode;

    if(xml.tokenType() != QXmlStreamReader::StartElement && xml.name() == "Region")
        return;

    QXmlStreamAttributes attributes = xml.attributes();
    if(attributes.hasAttribute("name") && attributes.hasAttribute("weight"))
    {
        regionNode = new NodeXml("Region", attributes.value("name").toString().toStdString(),
                                 attributes.value("weight").toUInt(), parent->depth + 1);
        parent->children.push_back(regionNode);
    }

    xml.readNext();

    while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "Region"))
    {
        if(xml.tokenType() == QXmlStreamReader::StartElement)
        {
            if(xml.name() == "Location")
                this->parseLocation(xml, regionNode);
        }
        xml.readNext();
    }
}

void Namespace::parseLocation(QXmlStreamReader &xml, NodeXml* parent)
{
    NodeXml* locationNode;

    if(xml.tokenType() != QXmlStreamReader::StartElement && xml.name() == "Location")
        return;

    QXmlStreamAttributes attributes = xml.attributes();
    if(attributes.hasAttribute("name") && attributes.hasAttribute("weight"))
    {
        locationNode = new NodeXml("Location", attributes.value("name").toString().toStdString(),
                                 attributes.value("weight").toUInt(), parent->depth + 1);
        parent->children.push_back(locationNode);
    }

    xml.readNext();

    while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "Location"))
    {
        if(xml.tokenType() == QXmlStreamReader::StartElement)
        {
            if(xml.name() == "Sector")
                this->parseSector(xml, locationNode);
        }
        xml.readNext();
    }

}

void Namespace::parseSector(QXmlStreamReader &xml, NodeXml* parent)
{
    NodeXml* sectorNode;

    if(xml.tokenType() != QXmlStreamReader::StartElement && xml.name() == "Sector")
        return;

    QXmlStreamAttributes attributes = xml.attributes();
    if(attributes.hasAttribute("name") && attributes.hasAttribute("weight"))
    {
        sectorNode = new NodeXml("Sector", attributes.value("name").toString().toStdString(),
                                 attributes.value("weight").toUInt(), parent->depth + 1);
        parent->children.push_back(sectorNode);
    }

    xml.readNext();

    while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "Sector"))
    {
        if(xml.tokenType() == QXmlStreamReader::StartElement)
        {
            if(xml.name() == "FileSystem")
                this->parseFileSystem(xml, sectorNode);
        }
        xml.readNext();
    }

}

void Namespace::parseFileSystem(QXmlStreamReader &xml, NodeXml* parent)
{
    NodeXml* filesystemNode;

    QXmlStreamAttributes attributes = xml.attributes();
    if(attributes.hasAttribute("name") && attributes.hasAttribute("weight"))
    {
        filesystemNode = new NodeXml("FileSystem", attributes.value("name").toString().toStdString(),
                                 attributes.value("weight").toUInt(), parent->depth + 1);
        parent->children.push_back(filesystemNode);
    }
}

