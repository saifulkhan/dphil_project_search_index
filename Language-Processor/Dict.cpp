#include "Dict.h"

CDict::CDict()
{
    OpenDict();
}

CDict::~CDict()
{
    mapDict.clear();
}

void CDict::OpenDict()
{

    // TODO: Commented
    /*
    string dict( "words.dict" );

	FILE *fpDict;
    if (( fpDict = fopen( (char*) dict.c_str(), "r") ) == NULL) {
        cout << __PRETTY_FUNCTION__ << "Can not open words.dict. Exiting..." << endl;
		exit(1);
	}
  
    int id;
    int freq;
	char word[16];
	while (fscanf(fpDict, "%s",  word) != EOF) {
        cout << word << endl;
        mapDict.insert( map<string, int>::value_type (word, 0) );
	}
	fclose(fpDict);
*/
}

bool CDict::IsWord(string &str) const
{
    //if (mapDict.find(str) != mapDict.end())
    //return true;
    return false;
}
