#include "Conversion.h"


string int64ToString(const int64_t& no)
{
    int64_t value = no;
    std::ostringstream os;
    os << value;
    return os.str();
}

double stringToDouble(const string &str)
{
    istringstream ss(str);
    double result;
    return ss >> result ? result : 0;
}


int64_t stringToInt64(const string &str)
{
    istringstream ss(str);
    int64_t result;
    return ss >> result ? result : 0;
}


wstring stringToWString(const string &s)
{
    wstring ws(s.begin(), s.end());
    return ws;
}


string wstringToString(const wstring &ws)
{
    string str(ws.begin(), ws.end());
    return str;
}


string stringToLower(const string &str)
{
    string _str = str;
    transform(_str.begin(), _str.end(), _str.begin(), ::tolower);

    return _str;
}



/*
 * http://stackoverflow.com/questions/3898840/converting-a-number-of-bytes-into-a-file-size-in-c
 */
char* convertSizeUnit(uint64_t size)
{
    static const char     *sizes[]   = { "EB", "PB", "TB", "GB", "MB", "KB", "B" };
    static const uint64_t    exbibytes = 1024ULL * 1024ULL * 1024ULL * 1024ULL * 1024ULL * 1024ULL;

    char     *result = new char[sizeof(char) * 20];
    uint64_t  multiplier = exbibytes;

    //qDebug() << __PRETTY_FUNCTION__ << "sizeof(sizes)= " << sizeof(sizes) << ", sizeof(*(sizes))= " << sizeof(*(sizes)) << ", DIM(sizes)= " << DIM(sizes);

    for (int i = 0; i < DIM(sizes); i++, multiplier /= 1024)
    {
        if (size < multiplier)
            continue;
        if (size % multiplier == 0)
            sprintf( result, "%llu %s", size / multiplier, sizes[i] );      // TODO:
        else
            sprintf( result, "%.1f %s", (float) size / multiplier, sizes[i] );

        //qDebug() << __PRETTY_FUNCTION__ << "result= " << result << ", sizes[i]= " << sizes[i] << endl;

        return result;
    }
    strcpy(result, "0");
    return result;

}

/*
 * n KB = byte, actual system size
 */
uint64_t unitToSize(const string sizeStr)
{
    if (sizeStr == "")
        return 0;

    uint64_t sizeB;

    string type = tokenise(sizeStr, " ").back();
    int    size = atoi(tokenise(sizeStr, " ").front().c_str());

    if (type.compare("GB") == 0)
        sizeB = size * pow(2, 30);
    else if (type.compare("MB") == 0)
        sizeB = size * pow(2, 20);
    else if (type.compare("KB") == 0)
        sizeB = size * pow(2, 10);
    else if (type.compare("B") == 0)
        sizeB = size;

    return sizeB;
}


/*
 * Mainly used by FSMapping.cpp for mapping, file attribute to glyph attribute
 */
double normalizeScale( double originalScale, double newScale, double originalValue )
{
    double newValue = ceil( originalValue / originalScale )  * newScale;
    return newValue;
}


/*
 * Source min = originalStart, max =originalEnd
 * Target scale min = newStart, max = newEnd
 * This function converts any originalValue between (originalStart - originalEnd) to newValue between (newStart, newEnd).
 */

double normalize( double originalStart, double originalEnd,  // original range
                  double newStart, double newEnd,            // desired range
                  double originalValue)                      // value to convert
{
    double newValue = newStart + ( ( (originalValue - originalStart) * (newEnd - newStart) ) / (originalEnd - originalStart) );
    return newValue;
}


void setBit(int &number, const unsigned &bit)
{
    number |= 1 << bit;
}


bool getBitVal(const int &number, const unsigned &bit)
{
    return ((number >> bit) & 1);
}
