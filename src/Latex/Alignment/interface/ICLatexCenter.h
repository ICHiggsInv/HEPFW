#ifndef LATEX_ALIGNMENT_ICLATEXCENTER
#define LATEX_ALIGNMENT_ICLATEXCENTER

#include "Latex/Core/interface/ICLatexEnvironment.h"

// C++ Included
#include <string>

class ICLatexCenter : public ICLatexEnvironment{
public:
  
  ICLatexCenter();
  //ICLatexTable(TH2* histogram);
  
  ~ICLatexCenter(){};

private:
  
  void init();
  
};

#endif