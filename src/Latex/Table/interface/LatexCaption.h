#ifndef LATEX_TABLES_LATEXCAPTION
#define LATEX_TABLES_LATEXCAPTION

#include "Latex/Core/interface/LatexObject.h"

// C++ Included
#include <string>

namespace hepfw{
  
  /***********************************************/
  /** \brief LaTeX Caption 
   * 
   * LaTeX caption
   ***********************************************/
  class LatexCaption : public LatexObject {
  public:
    
    LatexCaption();
    LatexCaption(const char* value);
    
    void       set(std::string value);
    
    std::string get();
    
    std::string toString();
    
  private:
    
    std::string m_caption; ///< Holds the caption text
    
  };
  
}

#endif