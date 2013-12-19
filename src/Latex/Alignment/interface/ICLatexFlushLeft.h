#ifndef LATEX_ALIGNMENT_ICLATEXFLUSHLEFT
#define LATEX_ALIGNMENT_ICLATEXFLUSHLEFT

#include "Latex/Core/interface/ICLatexEnvironment.h"

// C++ Included
#include <string>

class ICLatexFlushLeft : public ICLatexEnvironment{
public:
  
  ICLatexFlushLeft();
  //ICLatexTable(TH2* histogram);
  
  ~ICLatexFlushLeft(){};

private:
  
  void init();
  
};

#endif