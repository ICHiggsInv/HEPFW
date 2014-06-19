#ifndef PLOTS_STYLE_STYLE
#define PLOTS_STYLE_STYLE

#include "TStyle.h"

namespace rat{
  
  /***********************************************/
  /** \brief Style 
   * 
   * Style
   ***********************************************/
  class Style {
    
  public:
    
    Style();
    
    void setTDRStyle();
    
  public:  
    
    TStyle *tdrStyle;
    
  };

}

#endif
