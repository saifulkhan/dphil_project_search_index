#include "Wordnet.h"


namespace WN
{

Wordnet* Wordnet::m_wordnetInstance = NULL;


Wordnet* Wordnet::instance()
{
   if (!m_wordnetInstance)   // Only allow one instance of class to be generated.
       m_wordnetInstance = new Wordnet();

   return m_wordnetInstance;
}

Wordnet::~Wordnet()
{
    delete m_wordnetInstance;
}

Wordnet::Wordnet()
{
   //string wnDict = wordnet_path.file_string();
   //cout <<  wnDict << endl;
   const string& wnDict = DIR_WN_DIC;
   info = preprocess_wordnet(wnDict);
   info.update_pos_maps();


   load_wordnet(wnDict, *this, info);

   //FIXME: this check is only valid for Wordnet 3.0
   assert(info.nb_synsets() == 117659);

   // FIXME: Provide our path (via env var) ?
   // FIXME: rewrite this. not thread safe and slow
   //if(wninit())
   //  throw runtime_error("C wordnet lib initialization failed");
   //if (morphinit())
   //  throw runtime_error("C wordnet lib initialization failed");

   // The english dictionary to filter/optimize
   ifstream dic(ENGLISH_WORDS);
   string word;
   while (getline(dic, word))
        m_englishWords.push_back(word);
   dic.close();
}

string Wordnet::wordbase(const string& word, int ender)
{
   if (ends_with(word, info.sufx[ender]))
   {
     int sufxlen = info.sufx[ender].size();
     string strOut = word.substr(0, word.size() - sufxlen);
     if (!info.addr[ender].empty())
       strOut += info.addr[ender];
     return strOut;
   }
   return word;
}

 bool is_defined(const string&, pos_t)
 {
   throw "Not Implemented";
 }

 // Try to find baseform (lemma) of individual word in POS
 string Wordnet::morphword(const string& word, pos_t pos)
 {
   // first look for word on exception list
   map<string, string>::iterator it = exc[pos].find(word);
   if (it != exc[pos].end())
     return it->second; // found in exception list

   string tmpbuf;
   string end;
   int cnt = 0;

   if (pos == R)
     return ""; // Only use exception list for adverbs

   if (pos == N)
   {
     if (ends_with(word, "ful"))
     {
       cnt = word.size() - 3;
       tmpbuf = word.substr(0, cnt);
       end = "ful";
     }
     else
     {
       // check for noun ending with 'ss' or short words
       if (ends_with(word, "ss") || word.size() <= 2)
         return "";
     }
   }

   // If not in exception list, try applying rules from tables

   if (tmpbuf.size() == 0)
     tmpbuf = word;

   //offset = offsets[pos];
   //cnt = cnts[pos];

   int offset  = info.offsets[pos];
   int pos_cnt = info.cnts[pos];

   string morphed;
   for  (int i = 0; i < pos_cnt; i++)
   {
     morphed = wordbase(tmpbuf, (i + offset));
     if (morphed != tmpbuf) // && is_defined(morphed, pos))
       return morphed + end;
   }

   return morphed;
}


vector<synset> Wordnet::get_synsets(const string &word)
{
   set<synset> synsets;
   int counter = 0;
   Index light_index;
   light_index.lemma = word;

   //last pos is S and must not be given to morphword.
   static const unsigned nb_pos = POS_ARRAY_SIZE-1;
   for (unsigned p = 1; p <= nb_pos; p++)
   {
       //morphword Time consuming compare to path_similarity (x6)
       string mword = morphword(word, (pos_t)p);
       if (mword == "" && p != nb_pos)
           continue;
       if (mword == "")
           mword = word;
       light_index.lemma = mword;
       //cout << endl << "lemma "<< light_index.lemma << "\n";

       // binary_search
       pair<vector<Index>::iterator, vector<Index>::iterator> bounds =
               equal_range(indexList.begin(), indexList.end(), light_index);

       vector<Index>::iterator it;
       for (it = bounds.first; it != bounds.second; it++)
       {
           ++ counter;
           cout << "Counter= " << counter << "; lemma= " << it->lemma << ", pos= " << it->pos << endl;

           for (unsigned i = 0; i < it->synset_offsets.size(); i++)
           {
               int offset = it->synset_offsets[i];
               pos_t pos = it->pos;

               //map<int,int>& map = info.pos_maps[pos];
               //cout << "(" << offset << "/" << pos << ")" << endl;
               //cout << info.indice_offset[pos] << " + " << map[offset] << endl;

               if (pos == (pos_t)p)
               {
                   int u = info.compute_indice(offset, pos);
                   //cout << offsetWordList[u] << endl;
                   //synsets.insert(wordnet_graph[u]);

                   vector<string> words = offsetWordList[u];
                   for (unsigned j = 0; j < words.size(); ++j)
                       cout << words[j] << ", ";
                   cout << endl;
               }
           }
       }
    }

    cout << endl;
    //FIXME: get rid of this or return a set.
    vector<synset> synsetv(synsets.size());
    copy(synsets.begin(), synsets.end(), synsetv.begin());
    return synsetv;
}




void Wordnet::getSynsets(const string &term)
{
    cout << __PRETTY_FUNCTION__ ;

    static const unsigned nb_pos = POS_ARRAY_SIZE-1;
    for (unsigned p = 1; p <= nb_pos; p++)
    {
        vector<Index>::iterator it;
        for (it = indexList.begin(); it != indexList.end(); it++)
        {
            if (it->lemma.compare(term) == 0)
            {
                cout << "lemma= " << it->lemma << ", pos= " << it->pos << endl;
                // create lemma / node, and a directed-edge of type pos to
                // the below words / nodes

                for (unsigned i = 0; i < it->synset_offsets.size(); i++)
                {
                    int offset = it->synset_offsets[i];
                    pos_t pos = it->pos;
                    if (pos == (pos_t)p)
                    {
                        int u = info.compute_indice(offset, pos);
                        vector<string> words = offsetWordList[u];
                        printVec("Words:", words);
                    }
                }
            }
        }
    } // for pos
}


vector <string> Wordnet::getWordList(const int synset_offest)
{
    return offsetWordList[synset_offest];
}

vector <Ptr> Wordnet::getPtrList(const int synset_offest)
{
    return offsetPtrList[synset_offest];
}




/*
* Some terms in the wordnet are ignored, just to reduce the size
*/
bool Wordnet::filter(const string lemma)
{
    #ifdef DBG_WN
    cout << __PRETTY_FUNCTION__ << lemma << endl;
    #endif

    bool filter = (lemma.find("_") != string::npos) ||
                  (lemma.find_first_of("0123456789") != string::npos) ||
                  binary_search(m_englishWords.begin(), m_englishWords.end(), lemma) ||
                  (lemma.find("'") != string::npos);

    return filter;
}


template <class T>
void Wordnet::printVec(const string msg, vector<T> vec)
{
    cout << msg;
    for (unsigned i = 0; i < vec.size(); ++i)
        cout << vec[i] << ", ";
    cout << endl;
}

} // endof namespace wn
