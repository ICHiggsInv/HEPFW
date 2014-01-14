#ifndef LATEX_ALIGNMENT_ICLATEXFLUSHRIGHT
#define LATEX_ALIGNMENT_ICLATEXFLUSHRIGHT

#include "Latex/Core/interface/ICLatexEnvironment.h"

// C++ Included
#include <string>

class ICLatexFlushRight : public ICLatexEnvironment{
public:
  
  ICLatexFlushRight();
  //ICLatexTable(TH2* histogram);
  
  ~ICLatexFlushRight(){};

private:
  
  void init();
  
};

#endif