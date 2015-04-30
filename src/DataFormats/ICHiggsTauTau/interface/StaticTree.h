#ifndef ICHiggsTauTau_StaticTree
#define ICHiggsTauTau_StaticTree

#include "TTree.h"
#include <boost/functional/hash.hpp>

namespace ic {

struct StaticTree{
    static TTree *tree_;
};


}

#endif