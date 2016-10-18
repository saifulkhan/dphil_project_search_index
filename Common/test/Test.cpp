#include <iostream>
#include <iomanip>
#include <cstdlib>

#include "../Random.h"
#include "../FileTypes.h"
#include "../Conversion.h"
#include "../DateTime.h"
#include "../FileInfo.h"

using namespace std;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ PROTOTYPES  / Main~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void test_tokeniseStrToVector();
void test_FileInfoX();

void test_function();
void test_DateTime();
int  test_libconfig();
void test_fileSizeUnitConversion();
void test_unitToSize();
void testFileTypeXml();
void test_DateTime();


int main(int argc, char* argv[])
{
    test_FileInfoX();
    test_tokeniseStrToVector();
    test_unitToSize();
    //test_DateTime();
    //testFileTypeXml();

    //FileInfoX fileinfox();
    //cout << fileinfox;

    return EXIT_SUCCESS;
}


void test_FileInfoX()
{
    FileInfo f1(1234);
    cout << "f1: " << f1 << endl;
    FileInfo f2(3567);
    cout << "f2: " << f2 << endl;

    f1 = f2;
    cout << "f1: " << f1 << endl;
}


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ test_tokeniseStrToVector ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void test_tokeniseStrToVector()
{
    vector<string> vec1 = tokeniseStrToVector("apple computer hello", " ");

    for( vector<string>::const_iterator i = vec1.begin(); i != vec1.end(); ++i)
        cout << *i << ' ';

    cout << endl;
    vector<string> vec2 = tokeniseStrToVector(" ", " ");
    for( vector<string>::const_iterator i = vec2.begin(); i != vec2.end(); ++i)
        cout << *i << ' ';

    cout << endl;
    vector<string> vec3 = tokeniseStrToVector("apple computer , % hello #world", " ");
    for( vector<string>::const_iterator i = vec3.begin(); i != vec3.end(); ++i)
        cout << *i << ' ';

    cout << endl;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ DateTime ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void test_DateTime()
{
    DateTime dt1;

    DateTime dt;
    cout << dt.age("1999-02-03T23:00:00", "2000-12-01T23:00:00");
    cout << dt.age("1984-02-14T23:00:00", "2008-08-20T23:00:00");
    cout << dt.age("1960-06-14T23:00:00", "2008-07-14T23:00:00");
    cout << dt.age("1960-06-14T23:00:00", "2008-07-14T23:00:00");
    cout << dt.age("1960-05-05T23:00:00", "2008-07-13T23:00:00");
    cout << dt.age("2011-01-05T23:00:00", "2011-03-06T23:00:00");
    cout << dt.age("2000-12-01T23:00:00", "2000-12-01T23:00:00");
    cout << dt.age("2011-01-05T23:00:00", "2011-03-06T23:00:00");
    cout << dt.age("2011-01-05T23:00:00", "2011-03-06T23:00:00");
    cout << dt.age("2011-01-05T06:00:00", "2011-01-05T10:00:00");

    /*
     *
    // Used in cache
    DateTime dt;
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];
    time (&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer,80,"%Y-%m-%dT%H:%M:%S",timeinfo);
    string to(buffer);

    Cache* cache = Cache::instance();
    vector <FileInfo> tempVec = cache->search("draft");
    for (vector <FileInfo>::iterator i = tempVec.begin(); i != tempVec.end(); ++i)
    {
        FileInfoX fileInfoX(*i);
        fileInfoX.m_agex = (dt.age(fileInfoX.m_fileInfo.m_lastModified, to));
        //cout << fileInfoX.m_agex;
    }
     */

}


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ COMMON ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void testFileTypeXml()
{
    FileTypes* fileTypes = FileTypes::instance();

    map <string, string> typeCategoryMap = fileTypes->getTypeCategoryMap();
    for (map <string, string>::iterator it = typeCategoryMap.begin(); it != typeCategoryMap.end(); ++it)
         cout << it->first << ": " << it->second << endl;

    vector <string> fileCategoryList = fileTypes->getFileCatList();
    for (vector <string>::iterator it = fileCategoryList.begin(); it != fileCategoryList.end(); ++it)
        cout << *it << ", ";

    cout << endl;

}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Size Unit ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void test_fileSizeUnitConversion()
{
    // Test / usage: Converting a number of bytes into a file size
    int64_t  list[] = {   0, 1, 2, 34, 900, 1023, 1024, 1025, 2048, 1024 * 1024,
                          1024*1024*1024 + 1024*1024*400,
                          3221225472,
                          276583738175
                      };
    for (int i = 0; i < DIM(list); i++)
    {

        char *result =  convertSizeUnit(list[i]);
        cout << list[i] << "= " << result << endl;
        delete result;
    }

    cout << "1.70535E+11: " << convertSizeUnit(1.70535E+11) << endl;
}

void test_unitToSize()
{
    cout << unitToSize("2 B") << endl;
    cout << unitToSize("10000 B") << endl;
    cout << unitToSize("4 KB") << endl;
    cout << unitToSize("7 GB") << endl;
    cout << unitToSize("200 MB") << endl;
    cout << unitToSize("2000 MB") << endl;
}


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void test_randomNumber()
{
    // Test Random Bucket
    RandDraw bucket (5, 3);
    int i = 0;
    while ( i < 15)
    {
        cout << bucket.draw();
        i++;
    }

    // Test Random no.
    RandInt randNo;
    i = 0;
    while ( i < 15)
    {
        cout << randNo.getRandInt(0,1) << ", " << randNo.getRandInt (0,0) << ", "
             << randNo.getRandInt (5,5) << ", " << randNo.getRandInt (10,15) << endl;
        i++;
    }
}