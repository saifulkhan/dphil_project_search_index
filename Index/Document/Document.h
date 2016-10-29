#ifndef DOCUMENT_H_
#define DOCUMENT_H_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <map>
#include "stdHeader.h"

using namespace std;

class Field
{
public:	
    string name;
    string data;
    int  type;
	int  is_store;
	int  token;

public:
    Field();
    Field( int _type, int _is_store, int _token, string _name, string _data );
    virtual ~ Field();
};


class Document
{
public:
    map <string, Field*> m_fieldMap;

public:
	Document();
    virtual ~Document();

    void addField(string fieldName, Field *field);
    int32_t getIntField(string fieldName);
    std::int64_t getLongField(string fieldName );
    string  getStringField(string fieldName);
    bool containField(string fieldName);
};

#endif /*DOCUMENT_H_*/
