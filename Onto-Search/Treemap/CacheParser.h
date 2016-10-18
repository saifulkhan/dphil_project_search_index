#ifndef CACHEPARSER_H
#define CACHEPARSER_H

#include <iostream>

#include <FileInfo.h>
#include <Index.h>
#include "NodeTM.h"

using namespace std;

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Build from cache ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

class CacheParser {
private:
    vector<FileInfo> m_fileInfoVec;
    NodeTM* m_rootNode;

    NodeTM* updateSubtree(NodeTM* parent, vector<string> tokenQ);
    NodeTM* updateNode(NodeTM* parent, const FileInfo& fileInfo);
    void validateRootDir(const string& str, string* path, string* name);
    vector<string> subtreePath(const string &rootDirPath, const string& filePath);
    int64_t dirSize(NodeTM* item);

public:
    CacheParser();
    ~CacheParser();
    NodeTM* buildTree(const string rootDir = "/mnt");

};

#endif // CACHEPARSER_H
