#ifndef INFO_HELPER_HH
#define INFO_HELPER_HH

#include <string>
#include <stdexcept>
#include <map>
#include <assert.h>

#include "pos_t.h"

using namespace std;

namespace WN
{

struct info_helper;                                /// forward dec
info_helper preprocess_wordnet(const string& dn);  /// Create a new info_help based on wordnet data located in dn (../dict/)

/// Useful information for wordnet in-memory import
struct info_helper
{
    /// Symbols'split size
    static const size_t NB_SYMBOLS = 27;
    static const size_t NUMPARTS = 4;
    /// List of pointer symbols
    static const char *      symbols[NB_SYMBOLS];
    static const string sufx[];
    static const string addr[];
    ///
    static const int         offsets[NUMPARTS];
    static const int         cnts[NUMPARTS];
    ///
    typedef map<int,int>       i2of_t;     ///< indice/offset correspondences
    typedef map<pos_t, i2of_t> pos_i2of_t; ///< pos / map  correspondences
    pos_i2of_t pos_maps;
    size_t indice_offset[5];

    /// Constructor
    info_helper()
    {
        update_pos_maps();
    }

    /// Compute the number of synsets (i.e. the number of vertex in the graph)
    unsigned nb_synsets()
    {
        typedef pos_i2of_t::iterator iter_t;

        int sum = 0;
        for (iter_t it = pos_maps.begin(); it != pos_maps.end(); it++)
            sum += (*it).second.size();

        return sum;
        //return adj_map.size() + adv_map.size() + noun_map.size() + verb_map.size();
    };

    // Given a pos return the starting indice in the graph
    int get_indice_offset(pos_t pos)
    {
        return indice_offset[pos];
    };

    int get_symbol(const string& ps)
    {
        for (unsigned i = 0; i < NB_SYMBOLS; i++)
        if (ps == symbols[i])
          return i;

        // TODO- commented to avoid error binding with nodejs. Find a better way to handle runtime error. core dump?
        // Not put the assert ststement instead.
        //throw runtime_error("Symbol NOT FOUND.");
        assert(false);
    }

    //FIXME: use a hardcoded switch
    pos_t get_pos(char c)
    {
        unsigned i = 0;

        for (i = 0;  i < POS_ARRAY_SIZE; i++)
        if (c == POS_ARRAY[i])
            return pos_t(i);
        // TODO- commented to avoid error binding with nodejs. Find a better way to handle runtime error. core dump?
        // Not put the assert ststement instead.
        //throw runtime_error("pos NOT FOUND.");
        assert(false);
    }

    /// Helper function computing global indice in graph from local offset
    int compute_indice(int offset, pos_t pos);
    /// Update a map allowing one to get the correct map given a pos
    void update_pos_maps();

}; /// end of struct info_helper


} // endof namespace wn

#endif /* INFO_HELPER_HH */

