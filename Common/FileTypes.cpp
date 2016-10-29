#include "FileTypes.h"


FileTypes* FileTypes::m_instance = NULL;


FileTypes* FileTypes::instance()
{
   if (!m_instance)
       m_instance = new FileTypes();

   return m_instance;
}


FileTypes::~FileTypes()
{
    delete m_instance;
    m_instance = NULL;
}


FileTypes::FileTypes()
{
    parseXML(FILE_TYPES_XML);
}

/*
 * Tutorial on tinyxml http://www.dinomage.com/2012/01/tutorial-using-tinyxml-part-1/
 */

int FileTypes::parseXML(const string& xmlFile)
{

    TiXmlDocument doc;
    if(!doc.LoadFile(xmlFile))
    {
        cerr << doc.ErrorDesc() << endl;
        return EXIT_FAILURE;
    }

    TiXmlElement* root = doc.FirstChildElement();
    if (root == NULL)
    {
        cerr << "Failed to load file: No root element." << endl;
        doc.Clear();
        return EXIT_FAILURE;
    }

    //for (TiXmlElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement())
       //cout << elem->Value() << endl;

    parseCategory(root);
    doc.Clear();
}


void FileTypes::parseCategory(TiXmlElement* node)
{
    const char* categoryName;

    for (TiXmlElement* elem = node->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement())
    {
        string elemName = elem->Value();
        if(elemName == "Root" || elemName == "Link")       // Skip first two nodes
        {
            continue;
        }
        else if(elemName == "Category")
        {
            categoryName = elem->Attribute("name");
            if(categoryName != NULL)
            {
                #ifdef DBG_COMMON
                cout << __PRETTY_FUNCTION__ << "Category: " << categoryName << endl;
                #endif
                m_fileCatList.push_back(categoryName);
                parseType(elem, categoryName);
            }
        }
    }
}


void FileTypes::parseType(TiXmlElement* node, const string& categoryName)
{
    const char* typeName;

    for (TiXmlElement* elem = node->FirstChildElement("Type"); elem != NULL; elem = elem->NextSiblingElement("Type"))
    {
        typeName = elem->Attribute("name");
        if(typeName != NULL)
        {
            #ifdef DBG_COMMON
            cout << __PRETTY_FUNCTION__ << "Type: " << typeName << endl;
            #endif
            m_typeCategoryMap[typeName] = categoryName;
        }
    }
}