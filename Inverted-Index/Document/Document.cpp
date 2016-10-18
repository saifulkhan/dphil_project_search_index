#include "Document.h"


Field::Field()
{

}


Field::Field( int _type, int _is_store, int _token, string _name, string _data )
{
    type = _type;
    is_store = _is_store;
    token = _token;
    name = _name;
    data = _data;
}


Field::~ Field(){

}


/*************************************************************************************************
 *
 * Document
 *
 *************************************************************************************************/


Document::Document()
{

}


Document::~Document()
{
    for ( map <string,Field *>::iterator it = m_fieldMap.begin(); it != m_fieldMap.end(); ) {
		    delete it->second;
            m_fieldMap.erase( it++ );
	}
}


void Document::addField( string fieldName, Field *field )
{
    m_fieldMap[fieldName] = field;
}


int32_t Document::getIntField( string str )
{
    map <string,Field *>::iterator it = m_fieldMap.find( str );
    int32_t re = -1;

    if ( it != m_fieldMap.end() ) {
        Field *newField = (*it).second;
        re = atoi( newField->data.c_str() );
	}
	return re;
}


int64_t Document::getLongField( string str )
{
    map <string,Field *>::iterator it = m_fieldMap.find( str );
    int64_t re = -1;

    if ( it != m_fieldMap.end() ) {
        Field *newField = (*it).second;
        re = atoi( newField->data.c_str() );
	}
	return re;
}


string Document::getStringField( string str )
{
    map <string,Field *>::iterator it = m_fieldMap.find( str );
    string re = "";

    if ( it != m_fieldMap.end() ) {
        Field *newField = (*it).second;
        re = newField->data;
	}
	return re;
}


bool Document::containField( string fieldName )
{
    map <string, Field *>::iterator it = m_fieldMap.find( fieldName );

    if ( it != m_fieldMap.end() )
		return true;
	else
		return false;
}
