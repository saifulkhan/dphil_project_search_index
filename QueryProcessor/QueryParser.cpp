#include "QueryParser.h"

/*************************************************************************************************************************
 * Query DS
 *************************************************************************************************************************/

Query::Query() {}
Query::~Query() {}

void Query::print() {

    cout << "key: ";
    for (set<string>::const_iterator i = m_key.begin(); i != m_key.end(); ++i)
        cout << *i << ' ';

    cout << "| type: ";
    for (set<string>::const_iterator i = m_type.begin(); i != m_type.end(); ++i)
        cout << *i << ' ';

    cout << "| size: " << m_size.first << " " << m_size.second << endl;
}

/*************************************************************************************************************************
 * QueryParser
 *************************************************************************************************************************/

QueryParser::QueryParser() {}

QueryParser::~QueryParser() {}

Query QueryParser::parse(const string &queryString) {

    string keywords;
    string types;
    uint64_t sizeFrom = 0;
    uint64_t sizeTo = 0;

    json_spirit::Value v;
    json_spirit::read(queryString, v);
    const json_spirit::Object &obj = v.get_obj();

    for (json_spirit::Object::size_type i = 0; i != obj.size(); ++i) {

        const json_spirit::Pair &pair = obj[i];
        const string &name = pair.name_;
        const json_spirit::Value &value = pair.value_;

        if (name == "key") {
            //m_query.key(tokeniseStrToVector(value.get_str(), " "));
            keywords = value.get_str();

        } else if (name == "type") {
             //m_query.type(tokeniseStrToVector(value.get_str(), " "));
            types = value.get_str();

        } else if (name == "sizefrom") {
            sizeFrom = unitToSize(value.get_str());

        } else if (name == "sizeto") {
            sizeTo = unitToSize(value.get_str());

        } else if (name == "datefrom") {
            value.get_str();

        } else if (name == "dateto") {
            value.get_str();

        } else {
            assert(false);
        }
    }

    // Tokenise the kwyword and type
    m_tokeniser.tokenise(keywords);
    m_query.key(m_tokeniser.getTermSet());
    m_tokeniser.tokenise(types);
    m_query.type(m_tokeniser.getTermSet());

    m_query.size(pair<uint64_t, uint64_t> (min(sizeFrom, sizeTo), max(sizeFrom, sizeTo)));

    return m_query;
}
