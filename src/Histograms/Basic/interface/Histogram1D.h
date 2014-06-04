#ifndef HISTOGRAMS_DATAFORMATS_HISTOGRAM1D
#define HISTOGRAMS_DATAFORMATS_HISTOGRAM1D

#include "TH1D.h"

namespace at{
  
  class Histogram1D : public TH1D {
  public:
    
    Histogram1D();
    ~Histogram1D();
    
  };

};

#endif
