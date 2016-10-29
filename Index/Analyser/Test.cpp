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

    test_index_read();
    test_index_search();
    return EXIT_SUCCESS;
}



void test_index_search() {
    SE::Index* index = SE::Index::instance();
    vector <FileInfo> tempVec;
    tempVec = index->search("draft");
    cout << __PRETTY_FUNCTION__ << " Search results received: " << tempVec.size() << endl;

    for (vector<FileInfo>::iterator it = tempVec.begin(); it != tempVec.end(); ++it){
        cout << *it << endl;
    }

    index->close();
}

void  test_index_read() {
    SE::Index* index = SE::Index::instance();

    vector <FileInfo> tempVec;
    tempVec = index->read();
    cout << __PRETTY_FUNCTION__ << " Total files in index: " << tempVec.size() << endl;

    index->close();

}
 