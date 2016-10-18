#include "DateTime.h"


ostream& operator<<(ostream& os, const DT& dt)
{
    os << dt.m_year << "-" << dt.m_month << "-" << dt.m_day << " " << dt.m_hour << ":" << dt.m_min << ":" << dt.m_sec;
    return os;
}


DateTime::DateTime()
{
    m_monthDay = {31, 31, -1, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
}


DateTime::~DateTime()
{

}


string DateTime::age(const string& from, const string& to)
{
    m_fromDate  = toDT(from);
    m_toDate    = toDT(to);
    this->difference();

    #ifdef DBG_CACHE
    cout << "Difference: " << m_difference << endl;
    #endif

    stringstream ss;
    if (m_difference.m_year >= 10)
        ss << (m_difference.m_year / 10) << " " << "DE";
    else if (m_difference.m_year > 0)
        ss << m_difference.m_year  << " " << "Y";
    else if (m_difference.m_month > 0)
        ss << m_difference.m_month  << " " << "M";
    else if (m_difference.m_day > 0)
        ss << m_difference.m_day  << " " << "D";
    else if (m_difference.m_hour > 0)
        ss << m_difference.m_hour  << " " << "H";
    else
        ss << 0 << " " << "Hour";

    #ifdef DBG_CACHE
    cout << "Age: " << ss.str() << endl;
    #endif

    return ss.str();
}

void DateTime::difference()
{
    int increment   = 0;
    /*
     * Second calculation
     */
    if (m_fromDate.m_sec > m_toDate.m_sec)
    {
         m_difference.m_sec = (m_toDate.m_sec + 60) - m_fromDate.m_sec;
         increment          = 1;
    }
    else
    {
        m_difference.m_sec  = m_toDate.m_sec - m_fromDate.m_sec;
        increment           = 0;
    }

    /*
     * Minute calculation
     */
    if ((m_fromDate.m_min + increment) > m_toDate.m_min)
    {
         m_difference.m_min = (m_toDate.m_min + 24) - m_fromDate.m_min;
         increment          = 1;
    }
    else
    {
        m_difference.m_min  = m_toDate.m_min - m_fromDate.m_min;
        increment           = 0;
    }

    /*
     * Hour calculation
     */
    if ((m_fromDate.m_hour + increment) > m_toDate.m_hour)
    {
         m_difference.m_hour = (m_toDate.m_hour + 24) - m_fromDate.m_hour;
         increment           = 1;
    }
    else
    {
        m_difference.m_hour = m_toDate.m_hour - m_fromDate.m_hour;
        increment           = 0;
    }


    /*
     * Day calculation.
     */
    if ((m_fromDate.m_day + increment) > m_toDate.m_day)
    {
        increment = m_monthDay[m_toDate.m_month - 1];

        // Leap year
        if (increment == -1)
        {
            if (this->isLeapYear(m_toDate.m_year))
                increment = 29;
            else
                increment = 28;
        }

        m_difference.m_day = (m_toDate.m_day + increment) - m_fromDate.m_day;
        increment          = 1;
    }
    else
    {
        m_difference.m_day = (m_toDate.m_day + increment) - m_fromDate.m_day;
        increment          = 0;
    }

    /*
     * Month calculation.
     */
    if ((m_fromDate.m_month + increment) > m_toDate.m_month)
    {
       m_difference.m_month = (m_toDate.m_month + 12) - (m_fromDate.m_month + increment);
       increment            = 1;
    }
    else
    {
        m_difference.m_month = (m_toDate.m_month) - (m_fromDate.m_month + increment);
        increment            = 0;
    }

    /*
     * Year calculation.
     */
    m_difference.m_year = m_toDate.m_year - (m_fromDate.m_year + increment);
}


bool DateTime::isLeapYear(const int& year)
{
    if ((year % 400 == 0 || year % 100 != 0) && (year % 4 == 0))
        return true;
    else
        return false;
}

DT DateTime::toDT(const string& datetime)
{
    struct tm* ptr_tm ;
    time_t cTime;
    cTime = timestamp_to_ctime(datetime.c_str());
    ptr_tm = localtime(&cTime);

    DT dt;
    dt.m_year   = ptr_tm->tm_year + 1900;
    dt.m_month  = ptr_tm->tm_mon + 1;
    dt.m_day    = ptr_tm->tm_mday;
    dt.m_hour   = ptr_tm->tm_hour;
    dt.m_min    = ptr_tm->tm_min;
    dt.m_sec    = ptr_tm->tm_sec;

    #ifdef DBG_CACHE
    cout << datetime;
    printf(" Parsed to: %d-%d-%d %d:%d:%d \n" , ptr_tm->tm_year + 1900,\
            ptr_tm->tm_mon + 1 ,  ptr_tm->tm_mday, ptr_tm->tm_hour,\
            ptr_tm->tm_min, ptr_tm->tm_sec);
    #endif

    return dt;
}

/* convert string time stamp format to time_t and return */
time_t DateTime::timestamp_to_ctime(const char* time_stamp )
{

   time_t _return;
   struct tm tm_struct ;
   strptime(time_stamp ,"%Y-%m-%dT%H:%M:%S", &tm_struct);
   _return  = mktime(&tm_struct);   return
   _return;
}

