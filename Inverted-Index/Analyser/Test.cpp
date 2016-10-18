#include <string>
#include <iostream>
#include <fstream>

#include <DateTime.h>
#include <Index.h>
#include <vector>
#include <FileInfo.h>

using namespace std;

void test_index_search();
void test_index_read();

int main(int argc, char* argv[]) {
    /*
     * TODO: Run the analyzer
     */

    /*
     * Test functions
     */
     test_index_search();
     //test_index_read();
     return EXIT_SUCCESS;
}


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


void test_index_search() {
    SE::Index* index = SE::Index::instance();
    vector <FileInfo> tempVec;
    tempVec = index->search("draft");
    cout << __PRETTY_FUNCTION__ << " Search results received: " << tempVec.size() << endl;

    for (vector<FileInfo>::iterator it = tempVec.begin(); it != tempVec.end(); ++it){
        //cout << *it << endl;
        //FileInfoX fileInfoX(*it);
        //fileInfoX.m_agex = (dt.age(fileInfoX.m_fileInfo.m_lastModified, to));
        //cout << "Age: " << fileInfoX.m_agex << endl;
    }
}

void  test_index_read() {
    SE::Index* index = SE::Index::instance();

    vector <FileInfo> tempVec;
    tempVec = index->read();

    cout << __PRETTY_FUNCTION__ << " Total files in index: " << tempVec.size() << endl;

    for (vector<FileInfo>::iterator it = tempVec.begin(); it != tempVec.end(); ++it){
        cout << __PRETTY_FUNCTION__ << *it << endl;
        //FileInfoX fileInfoX(*it);
        //fileInfoX.m_agex = (dt.age(fileInfoX.m_fileInfo.m_lastModified, to));
        //cout << "Age: " << fileInfoX.m_agex << endl;
    }
}


void test_tokeniser() {
    Tokeniser tokeniser;
    tokeniser.tokenise("/building/construction/D/Dropbox/gratefulness/material/Search-Project/Server/LanguageProcessor/23-abr/saiful going apple dropbox khan $hello *book /private");

    cout << tokeniser.getTermString() << endl;
}



