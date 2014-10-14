#ifndef LATEX_ALIGNMENT_LATEXFLUSHRIGHT
#define LATEX_ALIGNMENT_LATEXFLUSHRIGHT

#include "Latex/Core/interface/LatexEnvironment.h"

// C++ Included
#include <string>

namespace hepfw{
  
  /***********************************************/
  /** \brief 
   * 
   * 
   ***********************************************/
  class LatexFlushRight : public LatexEnvironment{
  public:
    
    LatexFlushRight();
    ~LatexFlushRight(){};
    
  private:
    
    void init();
    
  };
  
}

#endif