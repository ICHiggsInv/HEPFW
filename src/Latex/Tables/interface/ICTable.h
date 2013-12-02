#ifndef LATEX_TABLES_ICTABLE
#define LATEX_TABLES_ICTABLE

#include "Latex/Core/interface/ICLatexEnvironment.h"

// C++ Included
#include <string>

class ICTable : public ICLatexEnvironment{
public:
  
  ICTable();
  //ICTable(TH2* histogram);
  
  ~ICTable(){};
  
  // set/get methods
  void setCentering(bool centering=true);
  void setLabel(std::string label);

private:

  // Private methods
  void        init();
  virtual std::string toStringEnvInner();
  
  // Private variables
  bool m_centering;
  
  std::string m_label;
  
  //ICTabular*      m_tabular;
  //ICTableCaption* m_caption;
  
};

#endif
