#include "Tokeniser.h"

Tokeniser::Tokeniser() {
    //m_wordnet = WN::Wordnet::instance();
}


Tokeniser::~Tokeniser() {

}


// TODO: FIXIT: Why this function is for??
void  Tokeniser::tokeniseStr(string s1) {

    cout << __PRETTY_FUNCTION__ << s1 << endl;

    while (!s1.empty()) {
        unsigned int len = s1.size();

        if (len > MAX_WORD_LENGTH) {
            len = MAX_WORD_LENGTH;
        }

        string w = s1.substr(0, len);// the candidate word
        bool isw = m_dict.IsWord(w);

        while (len > CHA_LENGTH && isw == false) {    // if not a word
            len -= CHA_LENGTH;        // cut a word
            w = w.substr(0, len);

            isw = m_dict.IsWord(w);
        }

        addTerm(w);
        //s2 += w + SEPARATOR;
        s1 = s1.substr(w.size());
    }
}


void Tokeniser::tokenise(string s1) {

    //cout << __PRETTY_FUNCTION__ << s1 << endl;

    m_termMap.clear();
    m_termSet.clear();
    m_termString = "";

    unsigned int i, len;
    unsigned char c;

    while (!s1.empty()) {
        i = 0;
        len = s1.size();
        c = s1[i];
        while (i < len && c < 128 && !((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))) {
            i++;
            c = s1[i];
        }

        if (i >= len)    //i has come to the end of s1
            break;
        if (i > 0)
            s1 = s1.substr(i);
        if (s1.empty())
            break;

        unsigned char ch = (unsigned char) s1[0];
        // deal with ASCII
        if (ch < 128) {
            i = 0;
            len = s1.size();
            c = s1[i];
            unsigned char cPre = c;
            while (i < len && c < 128 &&
                   (((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
                    && ((cPre >= 'a' && cPre <= 'z') || (cPre >= 'A' && cPre <= 'Z')))
                   || ((c >= '0' && c <= '9') && (cPre >= '0' && cPre <= '9'))
                    ) {
                i++;
                c = s1[i];
            }
            addTerm(s1.substr(0, i));

            if (i < len) {
                s1 = s1.substr(i);
                continue;
            } else {
                break;
            }

        } else if (ch < 176) {
            i = 0;
            len = s1.length();
            while (i < len && ((unsigned char) s1[i] < 176) && ((unsigned char) s1[i] >= 161)
                   && (!((unsigned char) s1[i] == 161 &&
                         ((unsigned char) s1[i + 1] >= 162 && (unsigned char) s1[i + 1] <= 168)))
                   && (!((unsigned char) s1[i] == 161 &&
                         ((unsigned char) s1[i + 1] >= 171 && (unsigned char) s1[i + 1] <= 191)))
                   && (!((unsigned char) s1[i] == 163 &&
                         ((unsigned char) s1[i + 1] == 172 || (unsigned char) s1[i + 1] == 161)
                         || (unsigned char) s1[i + 1] == 168 || (unsigned char) s1[i + 1] == 169 ||
                         (unsigned char) s1[i + 1] == 186
                         || (unsigned char) s1[i + 1] == 187 || (unsigned char) s1[i + 1] == 191))) {
                i = i + CHA_LENGTH;
            }

            if (i == 0)
                i = i + CHA_LENGTH;

            if (!(ch == 161 && (unsigned char) s1[1] == 161)) {
                if (i <= s1.size())
                    addTerm(s1.substr(0, i));
                else
                    break;
            }

            if (i <= s1.size())
                s1 = s1.substr(i);
            else
                break;

            continue;
        }

        i = CHA_LENGTH;
        len = s1.length();
        while (i < len && (unsigned char) s1[i] >= 176)
            i += CHA_LENGTH;

        cout << __PRETTY_FUNCTION__ << "Calling: tokeniseStr() with: " << s1 << endl;
        this->tokeniseStr(s1.substr(0, i));

        if (i < len)
            s1 = s1.substr(i);
        else
            break;
    } // while
}


void Tokeniser::addTerm(const string &t) {

    string term = stringToLower(t);

    //TODO: There are issues with this stemmer. Use better stemmer!
    //Porter2Stemmer::stem(term);

    map<string, int>::iterator it = m_termMap.find(term);
    if (it != m_termMap.end())
        m_termMap[term] = it->second + 1;
    else
        m_termMap[term] = 1;

    m_termSet.insert(term);
    m_termString += " " + term;
}
