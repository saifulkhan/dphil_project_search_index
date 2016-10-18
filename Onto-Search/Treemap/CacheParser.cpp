#include "CacheParser.h"

CacheParser::CacheParser() {
    m_rootNode = NULL;

    /*
     * Read the entire cache entry.
     */
    SE::Index* cache = SE::Index::instance();
    m_fileInfoVec = cache->read();
}


CacheParser::~CacheParser() {
    m_rootNode->deleteAll(m_rootNode);
}


NodeTM* CacheParser::buildTree(string rootDir) {

    //validateRootDir(rootDir);

    if(m_rootNode) {
        m_rootNode->deleteAll(m_rootNode);
    }
    // Create the root node
    m_rootNode = new NodeTM(FileInfo(0, rootDir, "", 0, "", "", "", "", "", ""), 0, 0);

    for(FileInfo fileInfo : m_fileInfoVec) {
        vector<string> list = subtreePath(rootDir, fileInfo.m_path);
        if (list.empty())
            continue;

        NodeTM* parent_of_leaf_node = updateSubtree(m_rootNode, list);

        #ifdef DBG_CACHEPARSER
        cout << __PRETTY_FUNCTION__ << fileInfo;
        cout << __PRETTY_FUNCTION__ << ": parent_of_leaf_node name= " << parent_of_leaf_node->fileInfo.m_fileName << ", path= " << parent_of_leaf_node->fileInfo.m_path << endl;
        #endif

        this->updateNode(parent_of_leaf_node, fileInfo); // The leafnode or file
     }

    this->dirSize(m_rootNode);
    return m_rootNode;
}


/*********************************************************************************************************
 * Build the tree, add the directory names as node
 *********************************************************************************************************/

NodeTM* CacheParser::updateSubtree(NodeTM* parent, vector<string> list)
{
    #ifdef DBG_CACHEPARSER
    cout << __FUNCTION__ << ": Parent_name= " << parent->fileInfo.m_fileName  << ", ";
    #endif

    if (!list.empty())
    {
        string children_name = list.front();
        list.erase(list.begin(), list.begin() + 1);

        string children_path;
        if (parent->fileInfo.m_path.empty())
            children_path = parent->fileInfo.m_fileName;
        else
            children_path = parent->fileInfo.m_path + "/" + parent->fileInfo.m_fileName;

        #ifdef DBG_CACHEPARSER
        cout << " Children_name= " << children_name << ", path= " << children_path << endl;
        #endif

        FileInfo fileInfo(0, children_name, "", 0, "", "", "", "", "", children_path);
        NodeTM* node = this->updateNode(parent, fileInfo);
        parent = this->updateSubtree(node, list);
    }
    return parent;
}


/*********************************************************************************************************
 * Iterates through all the children of the node (parent).
 * If a children of same name exists then return it, else create a new one.
 *********************************************************************************************************/

NodeTM* CacheParser::updateNode(NodeTM* parent, const FileInfo& fileInfo)
{
    #ifdef DBG_CACHEPARSER
    string children_path;
    if (parent->fileInfo.m_path.empty())
        children_path = parent->fileInfo.m_fileName;
    else
        children_path = parent->fileInfo.m_path + "/" + parent->fileInfo.m_fileName;
    cout << __FUNCTION__ << ": Name= " << fileInfo.m_fileName <<  ", Path= " <<  children_path << endl;
    #endif

    for (vector<NodeTM*>::iterator it = parent->children.begin(); it != parent->children.end(); ++it)
    {
        NodeTM* child = *it;
        if (child->fileInfo.m_fileName.compare(fileInfo.m_fileName) == 0) // has childern with the name?
        {
            #ifdef DBG_CACHEPARSER
            cout << __FUNCTION__ << ": Node exists, returning it." << endl;
            #endif

            return child;
        }
    }

    /*
     * No, create new node
     */
    #ifdef DBG_CACHEPARSER
    cout << __FUNCTION__ << ": Create new node at depth= " << parent->depth + 1 << endl;
    #endif

    NodeTM* newNode = new NodeTM(fileInfo, parent->depth + 1, fileInfo.m_size);
    parent->children.push_back(newNode);
    return newNode;
}


/*********************************************************************************************************
 * This function will tokenize the file path.
 * Ex. (/mnt /mnt/data/12) -> data 12
 *********************************************************************************************************/

vector<string> CacheParser::subtreePath(const string &rootDirPath, const string& filePath)
{
    vector<string> list;
    string str = filePath;
    size_t found = str.find(rootDirPath);

    #ifdef DBG_CACHEPARSER
    cout << __FUNCTION__ << ": " << rootDirPath << " found in "  <<  str << " at pos " << found << endl;
    #endif

    /*
     * Ex. if "/mnt/c" is found in "/mnt/c/data/2" on its beginning.
     * Then, delete it, else this path is ignored.
     */
    if (found != string::npos && found == 0)
        str.erase(str.begin(), (str.begin() + rootDirPath.length()));
    else
        return list;

    #ifdef DBG_CACHEPARSER
    cout << __FUNCTION__ << ": After removal of root path: " << str << endl;
    #endif

    string token;
    string delimiter = "/";

    while ((found = str.find(delimiter)) != string::npos)
    {
        token = str.substr(0, found);
        if(token.compare("") != 0)
            list.push_back(token);
        str.erase(0, found + delimiter.length());
    }
    if(str.compare("") != 0)
        list.push_back(str);

    return list;
}


/*********************************************************************************************************
 * Compute the "size" of the directories.
 *********************************************************************************************************/

int64_t CacheParser::dirSize(NodeTM* node)
{
    int64_t size = 0;
    vector<NodeTM*>::iterator it;

    // Sum of the file sizes under this node.
    for (it = node->children.begin(); it != node->children.end(); ++it)
    {
        if ((*it)->children.size() == 0) // files has no childern
            size += (*it)->value;
    }

   /*
    * Recurse directory.
    */
   for (it = node->children.begin(); it != node->children.end(); ++it)
   {
       if ((*it)->children.size() > 0) // directory has children
            size += this->dirSize(*it);
   }
    node->value = size;

    #ifdef DBG_TREEMAP
    cout << __PRETTY_FUNCTION__ << "Node: " << node->fileInfo.m_fileName << " Size= " << size << "/" << convertSizeUnit(size) << endl;
    #endif

    return size;
}

/*********************************************************************************************************
 * NOT USED,
 * TODO: Exception check the last character if "/", then delete.
 *********************************************************************************************************/

void CacheParser::validateRootDir(const string& str, string* path, string* name)
{
    // Case-1: /mnt/D  -> /mnt, D
    // Case-2: /mnt  -> / , mnt
    // case-3: /mnt/D/ -> /mnt, D    (or) /mnt/ -> / , mnt  (Not implemented)

    unsigned found = str.find_last_of("/\\");
    *name = str.substr(found + 1, string::npos);
    *path = str.substr(0, found);

    // Case-2
    if ((*path).compare("") == 0)
        *path = "/";
}
