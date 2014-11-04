#include "DataFormats/ICHiggsTauTau/interface/StaticTree.h"
#include "TTree.h"

namespace ic {
  
  TTree *ic::StaticTree::tree_ = NULL;
}