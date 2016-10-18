/*
 *
 */


#ifndef _DICT_H_040401_
#define _DICT_H_040401_

#include <stdlib.h> 
#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

class CDict
{
private:
    map<string, int> mapDict;

    void OpenDict();

public:
	CDict();
	~CDict();
	  
    bool GetFreq(string&) const
    {
        return false;
    }
    bool IsWord(string&) const;
    void AddFreq(string&)
    {

    }
};

#endif /* _DICT_H_040401_ */
