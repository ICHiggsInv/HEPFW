#ifndef HISTOGRAMS_DATAFORMATS_HISTOGRAM1F
#define HISTOGRAMS_DATAFORMATS_HISTOGRAM1F

#include "TH1F.h"

namespace at{

  class Histogram1F : public TH1F {
  public:
    
    Histogram1F();
    ~Histogram1F();
    
  };

}

#endif

