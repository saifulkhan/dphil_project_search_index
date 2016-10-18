#ifndef QUERY_H
#define QUERY_H

#include <vector>
#include <utility> // std::pair
#include <string>

using namespace std;

typedef struct Query Query;
struct Query
{
    int no;
    vector <string> name;
    vector <string> type;
    pair <double, double> size;   // byte
    //QDateTime mdatetime;
/*
    Query(vector <string> name = ,
          vector <string> type,
          pair <double, double> size)
    {
        this->name = name;
        this->type = type;
        this->size = size;
    }

    Query &operator=(const Query &q)
    {
        this->name = q.name;
        this->type = q.type;
        this->size = q.size;
        return *this;
    }

    Query(const Query &q)
    {
        this->name = q.name;
        this->type = q.type;
        this->size = q.size;
    }
*/


};

inline ostream& operator<<(ostream &os, const Query q)
{
    os << "name: ";
    for (unsigned i = 0; i < q.name.size(); ++i)
        os << q.name[i] << ", ";

    os << "type: ";
    for (unsigned i = 0; i < q.type.size(); ++i)
        os << q.type[i] << ", ";

    os << "size: " << q.size.first << ", " << q.size.second;

    os << endl;

    return os;
}

#endif // QUERY_H
