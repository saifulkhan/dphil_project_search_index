#ifndef _LOAD_WORDNET_HH
# define _LOAD_WORDNET_HH

# include "info_helper.h"

namespace WN
{
/// forward declaration
struct Wordnet;

/// Load the entire wordnet data base located in \p dn (typically .../dict/)
void load_wordnet(const std::string& dn, Wordnet& wn, info_helper& info);

} // endof namespace wn

#endif /* _LOAD_WORDNET_HH */

