#ifndef FILEINFO_H
#define FILEINFO_H

#include <iostream>
#include <vector>
#include <set>
#include "Conversion.h"
#include "FileTypes.h"
#include "DateTime.h"

using namespace std;

class FileInfo
{
public:
    // File metadata
    uint64_t m_docId;
    string m_fileName;      // complete file name, e.g., "Budget project.txt"
    string m_type;
    uint64_t m_size;
    string m_lastModified;
    string m_lastRead;
    string m_created;
    string m_user;
    string m_group;
    string m_path;          // Returns a file's path absolute path. This doesn't include the file name.

public:
    FileInfo(const uint64_t& docId      = 0,
             const string& fileName     = "",
             const string& type         = "",
             const uint64_t& size       = 0,
             const string& lastModified = "",
             const string& lastRead     = "",
             const string& created      = "",
             const string& user        = "",
             const string& group        = "",
             const string& path         = ""
            );

    FileInfo& operator=(const FileInfo& source);
    friend ostream& operator<<(ostream& os, const FileInfo& fileInfo);
};
ostream& operator<<(ostream& os, const FileInfo& fileInfo);


/*
 *  This is extended datastructure of FileInfo, containing search related information.
 *  Extended: search result info and actual file metadata/FileInfo
 */

class FileInfoX
{
public:
    bool m_select;
    double m_weight;
    string m_term;                      // actual term
    string m_termx;                     // expanded term
    string m_typex;                      // Extended to simplify type into categories.
    string m_sizex;                      // e.g, 768 KB
    string m_agex;                       // e.g, 64 Days, TODO:
    //File-meta-data
    FileInfo m_fileInfo;

public:
    FileInfoX(FileInfo fileInfo);
    bool operator<(const FileInfoX& info) const;
    FileInfoX& operator=(const FileInfoX& source);
    bool operator==(const FileInfoX& info) const;
    friend ostream& operator<<(ostream& os, const FileInfoX& fileInfoX);
};

ostream& operator<<(ostream& os, const FileInfoX& fileInfoX);


#endif // FILEINFO_H
