#ifndef _WORDNET_HH
#define _WORDNET_HH

#include <iostream>
#include <string>
#include <cassert>
#include <vector>
//Possible https://bugs.launchpad.net/ubuntu/+source/boost/+bug/270873
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <string>
#include <set>
#include <algorithm>
#include <stdexcept>
#include <boost/graph/breadth_first_search.hpp>
#include <boost/graph/filtered_graph.hpp>

#include "load_wordnet.h"
#include "pos_t.h"

using namespace std;

struct info_helper;

namespace WN
{

/// Index
struct Index
{
  string lemma;
  char  pos_;        /// unsafe pos
  int   synset_cnt;
  int   p_cnt;
  int   sense_cnt;
  float tagsense_cnt;
  vector<string> ptr_symbols;
  vector<int> synset_offsets;

  // extra
  vector<int> ids;
  pos_t pos;

  bool operator<(const Index& b) const
  {
    return (lemma.compare(b.lemma) < 0);
  }
};

/// More info here: http://wordnet.princeton.edu/wordnet/man/wndb.5WN.html
/// Synset
struct synset
{
  int  synset_offset_;
  int  lex_filenum;
  char ss_type_;
  int  w_cnt;
  vector<string> words;
  vector<int> lex_ids;
  int p_cnt;
  string gloss;

  // extra
  pos_t pos;        ///< pos
  int id;           ///< unique identifier

  bool operator==( const synset& s) const { return (id == s.id);  }
  bool operator<(const synset& s) const { return (id < s.id);   }
};



/// Rel between synsets properties
struct Ptr
{
  string pointer_symbol; // symbol of the relation
  int synsetid;     // unique identifier
  int source;       // source word inside synset
  int target;       // target word inside synset
};


/// Wordnet interface class
class Wordnet
{
private:
    //Singleton
    static Wordnet* m_wordnetInstance;
    Wordnet();
    Wordnet(Wordnet const&) { }
    // Wordnet& operator=(Wordnet const&) { } // TODO: Commented for nodejs warning

private:
    vector<string> m_englishWords;

public:
    info_helper        info;                               // helper object
    vector<Index> indexList;                              // index list
    map<pos_t, map<string, string> > exc;

    // parse data.pos and create
    // synset_offset, vector<word>
    map <int, vector<string> > offsetWordList;
    // synset_offset, vector<Ptr>
    map <int, vector<Ptr> > offsetPtrList;

 public:
    static Wordnet* instance();
    ~Wordnet();

    /// Return synsets matching word
    vector<synset> get_synsets(const string& word);
    //FIXME: todo
    vector<synset> get_synsets(const string& word, char pos);
    //FIXME: todo
    vector<synset> get_synset(const string& word, char pos, int i);
    // called by get_synsets
    string wordbase(const string& word, int ender);
    string morphword(const string& word, pos_t pos);

    inline bool ends_with(const std::string& str, const std::string& ending)
    {
        if (str.length() >= ending.length()) {
            int cmp = str.compare(str.length() - ending.length(), ending.length(), ending);
            return (0 == cmp);
        }
        return false;
    }

    void getSynsets(const string &term);
    vector <string> getWordList(const int synset_offest);
    vector <Ptr> getPtrList(const int synset_offest);

    // Others
    bool filter(const string lemma);

    template <class T>
    void printVec(const string str, vector<T> vec);


};


} // endof namespace wn
#endif /* _WORDNET_HH */

