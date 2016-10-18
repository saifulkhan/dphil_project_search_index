#ifndef DATETIME_H
#define DATETIME_H

#include <iostream>
#include <ctime>
#include <vector>
#include <sstream>

using namespace std;


class DT
{
public:
    int m_sec;
    int m_min;
    int m_hour;
    int m_day;
    int m_month;
    int m_year;

    friend ostream& operator<<(ostream& os, const DT& dt);
};


class DateTime
{
private:
    vector<int>  m_monthDay;
    DT           m_fromDate;
    DT           m_toDate;
    DT           m_difference;

    DT toDT(const string& datetime);
    time_t timestamp_to_ctime(const char* time_stamp);
    bool isLeapYear(const int& year);
    void difference();

public:
    DateTime();
    ~DateTime();
    string age(const string& from, const string& to);
};

#endif // DATETIME_H
