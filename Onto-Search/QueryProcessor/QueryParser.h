#ifndef QUERYPARSER_H
#define QUERYPARSER_H

#include <iostream>
#include <string>
#include <cassert>
#include <vector>
#include <json_spirit.h>

#include <FileInfo.h>
#include <DateTime.h>
#include <Conversion.h>
#include <Algorithm.h>

using namespace std;

/****************************************************************************************************************************************
 * {"key":"Apple","type":"","sizefrom":"","sizeto":"","datefrom":"","dateto":""}
 * Size Unit: "GB", "MB", "KB", "B"
 ****************************************************************************************************************************************/

class Query {
private:
    set<string> m_key;
    set<string> m_type;
    pair<uint64_t, uint64_t> m_size;
    pair <DateTime, DateTime>   m_date;

public:
    Query();
    ~Query();

    void key(const set<string> key) {
        m_key = key;
    }

    set<string> key() const {
        return m_key;
    }

    void const type(set<string> type) {
        m_type = type;
    }

    set<string> type() const {
        return m_type;
    }

    void size(const pair<uint64_t, uint64_t> size) {
        m_size = size;
    }

    pair<uint64_t, uint64_t> size() const {
        return m_size;
    }

    void print();
};


/*************************************************************************************************************************
 * Supporting class to parse/tokenize query
 *************************************************************************************************************************/



class QueryTokeniser {
private:
    const unsigned int MAX_WORD_LENGTH = 12;
    const unsigned int CHA_LENGTH = 3;

    map<string, int> m_termMap;
    set<string> m_termSet;
    string m_termString;

    void addTerm(const string &term);
    void tokeniseStr(string);

public:
    QueryTokeniser();
    ~QueryTokeniser();

    void tokenise(string);

    map<string, int> getTermMap() const {
        return m_termMap;
    }

    set<string> getTermSet() const {
        return m_termSet;
    }

    string getTermString() const {
        return m_termString;
    }
};

/*************************************************************************************************************************
 * QueryParser
 *************************************************************************************************************************/

class QueryParser {
private:
    Query m_query;
    QueryTokeniser m_tokeniser;

public:
    QueryParser();
    ~QueryParser();
    Query parse(const string &query);
};

#endif // QUERYPARSER_H
