#ifndef FILETYPES_H
#define FILETYPES_H

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <map>
#include <tinyxml.h>

//#define FILE_TYPES_XML @FILE_TYPES_XML@

using namespace std;

class FileTypes
{
// Singleton
private:
    static FileTypes* m_instance;
    FileTypes();
    FileTypes(FileTypes const&) { }
    //FileTypes& operator=(FileTypes const&) { } // TODO: Commented for nodejs warning

private:
    map <string, string> m_typeCategoryMap;
    map <string, string> m_typeDescriptionMap;
    vector <string> m_fileCatList;

    int parseXML(const string &xmlFile);
    void parseCategory(TiXmlElement* node);
    void parseType(TiXmlElement* node, const string& categoryName);

public:
    ~FileTypes();
    static FileTypes* instance();
    map <string, string> getTypeCategoryMap() const { return m_typeCategoryMap; }
    vector <string> getFileCatList() const { return m_fileCatList; }
    map <string, string>  getTypeDescriptionMap() const { return m_typeDescriptionMap; }
};

#endif // FILETYPES_H
