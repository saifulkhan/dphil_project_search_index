#include "Algorithm.h"

/*
 * String tokenise and return a vector
 * ref: http://www.oopweb.com/CPP/Documents/CPPHOWTO/Volume/C++Programming-HOWTO-7.html
 */
vector<string> tokeniseStrToVector(const string& str, const string& delimiters)
{
    vector<string> tokens;

    // Skip delimiters at beginning.
    string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    // Find first "non-delimiter".
    string::size_type pos     = str.find_first_of(delimiters, lastPos);

    while (string::npos != pos || string::npos != lastPos)
    {
        // Found a token, add it to the vector.
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        // Skip delimiters.  Note the "not_of"
        lastPos = str.find_first_not_of(delimiters, pos);
        // Find next "non-delimiter"
        pos = str.find_first_of(delimiters, lastPos);
    }

    return tokens;
}

/*
 * String tokenise and return a Queue
 * TODO: Improve this code (use regex?) 
 */
queue<string> tokenise(const string &str, const string &delimiter)
{
    string s = str;
    queue<string> q;

    size_t pos = 0;
    string token;
    while ((pos = s.find(delimiter)) != std::string::npos)
    {
        token = s.substr(0, pos);
        if(token.compare("") != 0)
            q.push(token);
        s.erase(0, pos + delimiter.length());
    }
    if(s.compare("") != 0)
        q.push(s);
    return q;
}
