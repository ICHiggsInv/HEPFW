#ifndef HISTOGRAMS_DATAFORMATS_HISTOGRAM1F
#define HISTOGRAMS_DATAFORMATS_HISTOGRAM1F

#include "TH1F.h"

namespace rat{

  /***********************************************/
  /** \brief Histogram1F
   * 
   * Histogram1F
   ***********************************************/
  class Histogram1F : public TH1F {
  public:
    
    Histogram1F();
    ~Histogram1F();
    
  };

}

#endif

