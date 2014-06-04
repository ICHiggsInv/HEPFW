#ifndef LATEX_TABLES_ICLATEXTABLE
#define LATEX_TABLES_ICLATEXTABLE

#include "Latex/Core/interface/ICLatexEnvironment.h"

// C++ Included
#include <string>

/***********************************************/
/** \brief LaTeX Table
 * 
 * This class allows creation and manipulation of a LaTeX table from C++
 * code. 
 ***********************************************/
class ICLatexTable : public ICLatexEnvironment{
public:
  
  ICLatexTable();
  //ICLatexTable(TH2* histogram);
  
  ~ICLatexTable(){};
  
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

#endif
