#ifndef HISTOGRAMS_DATAFORMATS_HISTOGRAM2D
#define HISTOGRAMS_DATAFORMATS_HISTOGRAM2D

#include "TH2D.h"

namespace at{

  class Histogram2D : public TH2D {
  public:
    
    Histogram2D();
    ~Histogram2D();
    
  };

}

#endif

