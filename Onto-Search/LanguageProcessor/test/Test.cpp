#include <iostream>
#include <iomanip>
#include <cstdlib>

#include "../Wordnet.h"
#include "../Porter2Stemmer.h"

using namespace std;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ PROTOTYPES  / Main~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void test_Wordnet();
void test_Stemmer();


int main(int argc, char* argv[])
{
    cout << "LanguageProcessor: test..." << endl;
    //test_Wordnet();
    //test_Stemmer();
    return EXIT_SUCCESS;
}


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ LANGUAGE PROCESSOR ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void test_Wordnet()
{
    WN::Wordnet* wordnet = WN::Wordnet::instance();
    wordnet->get_synsets("draft");
}



void test_Stemmer()
{
    string word = "going";
    Porter2Stemmer::stem(word);
    cout << __PRETTY_FUNCTION__ << word << endl;

    word = "on";
    cout << __PRETTY_FUNCTION__ << word << endl;


}
