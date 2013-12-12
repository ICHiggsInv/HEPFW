#ifndef FWCORE_DATAFORMATS_ICINT
#define FWCORE_DATAFORMATS_ICINT

#include "FWCore/DataFormats/interface/ICDataType.h"

// C++ Included
#include <string>

class ICInt : public ICDataType {
public:

  ICInt();
  ICInt(int input);
  
  int get();
  
protected:

  int m_var;
  
};

#endif