#include "GenSimFiles.h"

vector<string> GenSimFiles::m_dns = {"nfs1", "nfs2", "ntfs"}; // Directory name

GenSimFiles::GenSimFiles(unsigned numFiles) : m_numFiles(numFiles)
{
    FileTypes *fileTypes = FileTypes::instance();
    m_typeCategoryMap = fileTypes->getTypeCategoryMap();

    m_typeDist = new DiscreteDist(FILE_TYPE_STAT);
    m_nameDist = new DiscreteDist(FILE_NAME_STAT);
    m_userDist = new DiscreteDist(FILE_USER_STAT);
    m_groupDist = new DiscreteDist(FILE_GROUP_STAT);

    m_datafile.open(FILE_SIM_DATA);
}


GenSimFiles::~GenSimFiles()
{
    m_datafile.close();
}

void GenSimFiles::generateFiles(const uint64_t& id)
{
    string type     = m_typeDist->generate();
    string name     = this->baseName() + "." + type;
    int64_t size    = this->size(type);
    string path     = this->path();
    string dateTime = m_timeDistribution.generate();
    string user     = m_userDist->generate();
    string group    = m_groupDist->generate();

    // The output should be redirected to a csv file
    m_datafile << id << ","
               << name << ","
               << type << ","
               << size << ","
               << dateTime << ","
               << path << ","
               << user << ","
               << group <<  ","
               << convertSizeUnit(size) << endl;

    //cout << name << "," <<  type << "," << size << "," << dateTime << "," << path << ", " << convertSizeUnit(size) << endl;
}


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ NAME  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  */

string GenSimFiles::baseName()
{
    string baseName = m_nameDist->generate() + " " +
                      m_nameDist->generate() + " " +
                      m_nameDist->generate() + " " +
                      m_nameDist->generate();
    return baseName;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ SIZE  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  */

/*
 * Before generating a size, find the category of the file.
 * The distribution will depend on the category(type).
 */
int64_t GenSimFiles::size(const string& type)
{
    AbstractContDist *dist;
    string category;

    try
    {
        category = m_typeCategoryMap.at(type);
    }
    catch (const std::out_of_range& oor)
    {
       cout << "out_of_range:" << type << endl;
       return 0;
    }

    if (category.compare("Audio") == 0)
        dist = ContDistFactory::getContDist(DistType::audio);

    else if (category.compare("Backup") == 0)
        dist = ContDistFactory::getContDist(DistType::backup);

    else if (category.compare("Compressed") == 0)
        dist = ContDistFactory::getContDist(DistType::compressed);

    else if (category.compare("Database") == 0)
        dist = ContDistFactory::getContDist(DistType::database);

    else if (category.compare("Developer") == 0 || category.compare("CAD") == 0)
        dist = ContDistFactory::getContDist(DistType::developer);

    else if (category.compare("DiskImage") == 0)
        dist = ContDistFactory::getContDist(DistType::diskimage);

    else if (category.compare("Document") == 0 || category.compare("Spreadsheet") == 0 || category.compare("Presentation") == 0)
        dist = ContDistFactory::getContDist(DistType::document);

    else if (category.compare("Executable") == 0)
        dist = ContDistFactory::getContDist(DistType::executable);

    else if (category.compare("Image") == 0)
        dist = ContDistFactory::getContDist(DistType::image);

    else if (category.compare("Misc") == 0)
        dist = ContDistFactory::getContDist(DistType::misc);

    else if (category.compare("System") == 0)
        dist = ContDistFactory::getContDist(DistType::sys);

    else if (category.compare("Video") == 0)
        dist = ContDistFactory::getContDist(DistType::video);

    else if (category.compare("Web") == 0)
        dist = ContDistFactory::getContDist(DistType::web);
    else
        assert(false);  // should not happen

    int64_t size = 0;   // when the drawn/generated size is 0, but the file size should not be zero.
    do
    {
        size = dist->generate();
    } while (size == 0);

    return size;
}


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ DIR NAMESPACEs  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  */

string GenSimFiles::path()
{
    NodeXml* node = m_namespace.rootNode();
    string path = "/mnt";
    this->constructPath(node, &path);

    #ifdef DBG_DATA
    cout << __PRETTY_FUNCTION__ << "path (before adding variable length): " << path << endl;
    #endif

    // Additional variable length
    for (unsigned int i = 0; i < rand() % m_dns.size(); ++i)
    {
        path += "/" + m_dns[rand() % m_dns.size()];
    }

    return path;
}

/*
 *  From the XML structure
 */
void GenSimFiles::constructPath(NodeXml* parent, string* str)
{
    if(parent->children.empty())
        return;

    vector <string> elementVec;
    vector <int> weightVec;
    for (NodeXml* node : parent->children)
    {
        elementVec.push_back(node->name);
        weightVec.push_back(node->weight);
    }

    m_discreteDist.initialise(elementVec, weightVec);
    string nodeName = m_discreteDist.generate();
    *str = *str + "/" + nodeName;

    for (NodeXml* node : parent->children)
    {
        if (node->name.compare(nodeName) == 0)
            constructPath(node, str);
    }
}
