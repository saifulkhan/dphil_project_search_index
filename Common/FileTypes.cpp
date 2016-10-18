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




// Old code using QtXml parser

#if 0
void FileTypes::parseXML(const string &xmlFile)
{
    /* We'll parse the example.xml */
    QFile* file = new QFile(QString::fromStdString(xmlFile));
    /* If we can't open it, let's show an error message. */
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
    {
       return;
    }
    /* QXmlStreamReader takes any QIODevice. */
    QXmlStreamReader xml(file);
    QList< QMap<QString,QString> > persons;
    /* We'll parse the XML until we reach end of it.*/
    while(!xml.atEnd() && !xml.hasError())
    {
        /* Read next element.*/
        QXmlStreamReader::TokenType token = xml.readNext();
        /* If token is just StartDocument, we'll go to next.*/
        if(token == QXmlStreamReader::StartDocument)
        {
            continue;
        }
        /* If token is StartElement, we'll see if we can read it.*/
        if(token == QXmlStreamReader::StartElement)
        {
            /* If it's named Filetypes/Link, we'll go to the next.*/
            if(xml.name() == "Filetypes" || xml.name() == "Link")
                continue;

            /* If it's named Category, we'll dig the information from there.*/
            if(xml.name() == "Category")
                parseCategory(xml);

        }
    }
    /* Error handling. */
    if(xml.hasError())
    {
    //        QMessageBox::critical(this,
    //                              "FileTypes::parseXML",
    //                              xml.errorString(),
    //                              QMessageBox::Ok);
    }
    /* Removes any device() or data from the reader
     * and resets its internal state to the initial state. */
    xml.clear();
}


void  FileTypes::parseCategory(QXmlStreamReader &xml)
{
    string category;

    /* Let's check that we're really getting a Category. */
    if(xml.tokenType() != QXmlStreamReader::StartElement && xml.name() == "Category")
        return;

    /* Let's get the attributes for person */
    QXmlStreamAttributes attributes = xml.attributes();
    /* Let's check that person has id attribute. */
    if(attributes.hasAttribute("name"))
    {
        /* We'll add it to the pair. */
        category = attributes.value("name").toString().toStdString();
        m_fileCatList.push_back(category);
    }
    /* Next element... */
    xml.readNext();
    /*
     * We're going to loop over the things because the order might change.
     * We'll continue the loop until we hit an EndElement named Category.
     */
    while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "Category"))
    {
        if(xml.tokenType() == QXmlStreamReader::StartElement)
        {
            /* We've found first name. */
            if(xml.name() == "Type")
            {
                string type;
                parseType(xml, type);
                m_typeCategoryMap[type] = category;
            }
        }
        /* ...and next... */
        xml.readNext();
    }
}

// Returns: <name, desc>, e.g., <doc, word document file>
void FileTypes::parseType(QXmlStreamReader &xml, string &type)
{
    /* Let's get the attributes for <Type .... ></Type> */
    QXmlStreamAttributes attributes = xml.attributes();
    /* Let's check it has name and desc attribute. */
    if(attributes.hasAttribute("name") && attributes.hasAttribute("desc"))
    {
        type = attributes.value("name").toString().toStdString();
        string desc = attributes.value("desc").toString().toStdString();
        m_typeDescriptionMap[type] = desc;
        //cout << type << ", " << desc << endl;
    }
}

#endif
