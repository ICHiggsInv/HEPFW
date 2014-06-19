#ifndef HISTOGRAMS_BASIC_HISTOGRAM1D
#define HISTOGRAMS_BASIC_HISTOGRAM1D

#include "TH1D.h"

namespace rat{

  /***********************************************/
  /** \brief Histogram1D 
   * 
   * Histogram1D
   ***********************************************/
  class Histogram1D : public TH1D {
  public:
    
    Histogram1D();
    ~Histogram1D();
    
  };

};

#endif
