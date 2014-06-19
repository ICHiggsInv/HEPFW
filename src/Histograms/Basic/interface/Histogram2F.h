#ifndef HISTOGRAMS_DATAFORMATS_HISTOGRAM2F
#define HISTOGRAMS_DATAFORMATS_HISTOGRAM2F

#include "TH2F.h"

namespace rat{

  /***********************************************/
  /** \brief Histogram2F
   * 
   * Histogram2F
   ***********************************************/
  class Histogram2F : public TH2F {
  public:
    
    Histogram2F();
    ~Histogram2F();
    
  };

}

#endif
 
