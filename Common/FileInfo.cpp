#include "FileInfo.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ FILEINFO ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*
 * Mainly used when we use simulated data.
 */
FileInfo::FileInfo(const uint64_t& docId,
                   const string& fileName,
                   const string& type,
                   const uint64_t& size,
                   const string& lastModified,
                   const string& lastRead,
                   const string& created,
                   const string& user,
                   const string& group,
                   const string& path)
{
    this->m_docId        = docId;
    this->m_fileName     = fileName;
    this->m_type         = type;
    this->m_size         = size;
    this->m_lastModified = lastModified;
    this->m_lastRead     = lastRead;
    this->m_created      = created;
    this->m_user        = user;
    this->m_group        = group;
    this->m_path         = path;
}

FileInfo& FileInfo::operator=(const FileInfo &source)
{
    this->m_docId        = source.m_docId;
    this->m_fileName     = source.m_fileName;
    this->m_type         = source.m_type;
    this->m_size         = source.m_size;
    this->m_lastModified = source.m_lastModified;
    this->m_lastRead     = source.m_lastRead;
    this->m_created      = source.m_created;
    this->m_user        = source.m_user;
    this->m_group        = source.m_group;
    this->m_path         = source.m_path;

    return *this;

}


/*
 * http://msdn.microsoft.com/en-us/library/vstudio/1z2f6c2k.aspx
 */
ostream& operator<<(ostream& os, const FileInfo& fileInfo)
{
    os << "DocID: "         << fileInfo.m_docId
       << ", FileName: "    << fileInfo.m_fileName
       << ", Type: "        << fileInfo.m_type
       << ", Size: "        << fileInfo.m_size
       << ", LastModified: "<< fileInfo.m_lastModified
       << ", LastRead: "    << fileInfo.m_lastRead
       << ", Created: "     << fileInfo.m_created
       << ", Owner: "       << fileInfo.m_user
       << ", Group: "       << fileInfo.m_group
       << ", Path: "        << fileInfo.m_path
          ;
    return os;
}


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ FILEINFOX ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

FileInfoX::FileInfoX(FileInfo fileInfo)
{
    this->m_fileInfo = fileInfo;
    this->m_select   = false;
    this->m_weight   = 1.0;
    this->m_term     = "";
    this->m_termx    = "";

    FileTypes *fileTypes = FileTypes::instance();
    this->m_typex        = fileTypes->getTypeCategoryMap()[m_fileInfo.m_type];
    this->m_sizex        = convertSizeUnit(m_fileInfo.m_size);

    // TODO: Optimize, this part is called repeatedly.
    DateTime dateTime;
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];
    time (&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer, 80, "%Y-%m-%dT%H:%M:%S", timeinfo);
    string to(buffer);
    this->m_agex = dateTime.age(fileInfo.m_lastModified, to);
}


/*
 *  This is used to sort the search result (file list)
 *  Usage- std::sort(vec.begin(), vec.end());
 */
bool FileInfoX::operator<(const FileInfoX &info) const
{
    //return (this->m_weight > info.m_weight);
    return (this->m_fileInfo.m_docId < m_fileInfo.m_docId);
}

FileInfoX& FileInfoX::operator=(const FileInfoX &source)
{
    this->m_fileInfo = source.m_fileInfo;
    this->m_select   = source.m_select;
    this->m_weight   = source.m_weight;
    this->m_term     = source.m_term;
    this->m_termx    = source.m_termx;
    this->m_typex    = source.m_typex;
    this->m_sizex    = source.m_sizex;
    this->m_agex     = source.m_agex;

    return *this;
}

bool FileInfoX::operator==(const FileInfoX &info) const
{
    return (this->m_fileInfo.m_docId > info.m_fileInfo.m_docId);
}



ostream& operator<<(ostream& os, const FileInfoX& fileInfo)
{
    os << "Select: "   << fileInfo.m_select
       << ", Weight: " << fileInfo.m_weight;

    cout << fileInfo.m_fileInfo;
    return os;
}


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ FILEINFO unused ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#if 0
/*
 * Useful when we use real file system data, gives us QFileInfo
 */
FileInfo::FileInfo(const QFileInfo &qFileInfo)
{
    this->m_fileName     = qFileInfo.fileName().toStdString();
    this->m_type         = stringToLower(qFileInfo.suffix().toStdString());
    this->m_size         = qFileInfo.size();
    this->m_lastModified = qFileInfo.lastModified().toString(Qt::ISODate).toStdString();
    this->m_lastRead     = qFileInfo.lastRead().toString(Qt::ISODate).toStdString();
    this->m_created      = qFileInfo.created().toString(Qt::ISODate).toStdString();
    this->m_user        = qFileInfo.user().toStdString();
    this->m_group        = qFileInfo.group().toStdString();
    this->m_path         = qFileInfo.absolutePath().toStdString();
}
#endif
