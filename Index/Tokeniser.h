/***********************************************************************************************************************
 * 1. Tokenize the input string.
 * 2. Creates <term, frequency> map
 * 3. Use Porter2Stemmer for stemming
 * 4. TODO: remove stop-word (implement separately)
 * 5. TODO: Uses Dict class to filter out non-dictionary terms which is actually not required (?).
 **********************************************************************************************************************/

#ifndef _TOKENISER_
#define _TOKENISER_

#include <iostream>
#include <string>
#include <map>
#include <set>

#include <Conversion.h>

using namespace std;

const unsigned int MAX_WORD_LENGTH = 12;
const unsigned int CHA_LENGTH =3;
const string SEPARATOR("/  ");          // delimiter between words

class Tokeniser {
private:
    map<string, int> m_termMap;
    set<string> m_termSet;
    string m_termString;

    void addTerm(const string &term);
    void tokeniseStr(string);

public:
    Tokeniser();
    ~Tokeniser();

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
	
#endif /* _TOKENISER_ */
