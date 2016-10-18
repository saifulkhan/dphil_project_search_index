#ifndef _POS_T_HH
#define _POS_T_HH

# include <string>
# include <sstream>
# include <fstream>
# include <algorithm>
# include <stdexcept>
using namespace std;

namespace WN
{

static const size_t POS_ARRAY_SIZE = 5;
static const char POS_ARRAY[POS_ARRAY_SIZE] = {'s', 'n', 'v', 'a', 'r'};

enum pos_t
{
      S       = 0,
      N       = 1,
      V       = 2,
      A       = 3,
      R       = 4,
      UNKNOWN	= 5,
};


inline pos_t get_pos_from_name(const string& pos)
{
  if (pos == "adj")
    return A;
  if (pos == "noun")
    return N;
  if (pos == "adv")
    return R;
  if (pos == "verb")
    return V;
  return UNKNOWN;
}

inline string get_pos_from_enum(const pos_t &pos)
{
  if (pos == 0)
    return "S";
  if (pos == 1)
    return "N";
  if (pos == 2)
    return "V";
  if (pos == 3)
    return "A";
  if (pos == 4)
    return "R";

  return "UNKNOWN";
}

} // endof namespace wn

#endif /* _POS_T_HH */

