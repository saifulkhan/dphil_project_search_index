#include <iostream>
#include <iomanip>
#include <cstdlib>

#include "../Tokeniser.h"
#include "../Wordnet.h"
#include "../Porter2Stemmer.h"

using namespace std;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ PROTOTYPES  / Main~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void test_Wordnet();
void test_Tokeniser();
void test_Stemmer();


int main(int argc, char* argv[])
{
    cout << "LanguageProcessor: test..." << endl;
    //test_Wordnet();
    test_Tokeniser();
    //test_Stemmer();

    return EXIT_SUCCESS;
}


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ LANGUAGE PROCESSOR ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void test_Wordnet()
{
    WN::Wordnet* wordnet = WN::Wordnet::instance();
    wordnet->get_synsets("draft");
}

void test_Tokeniser()
{
    Tokeniser tokeniser;
    tokeniser.tokenise("/building/construction/D/Dropbox/gratefulness/material/Search-Project/Server/LanguageProcessor/23-abr/saiful going apple dropbox khan $hello *book /private");

    cout << tokeniser.getTermString() << endl;
}

void test_Stemmer()
{
    string word = "going";
    Porter2Stemmer::stem(word);
    cout << __PRETTY_FUNCTION__ << word << endl;

    word = "on";
    cout << __PRETTY_FUNCTION__ << word << endl;


}
