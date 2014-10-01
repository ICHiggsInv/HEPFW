#ifndef LATEX_TABLES_LATEXTABLE
#define LATEX_TABLES_LATEXTABLE

#include "Latex/Core/interface/LatexEnvironment.h"

// C++ Included
#include <string>

namespace hepfw{
  
  /***********************************************/
  /** \brief LaTeX Table
   * 
   * This class allows creation and manipulation of a LaTeX table from C++
   * code. 
   ***********************************************/
  class LatexTable : public hepfw::LatexEnvironment{
  public:
    
    LatexTable();
    //LatexTable(TH2* histogram);
    
    ~LatexTable(){};
    
    // set/get methods
    void setLabel(std::string label);
    
  private:
    
    // Private methods
    void        init();
    virtual std::string toStringEnvInner();
    
    // Private variables  
    std::string m_label;
    
    //ICTabular*      m_tabular;
    //ICLatexTableCaption* m_caption;
    
  };
  
}

#endif
