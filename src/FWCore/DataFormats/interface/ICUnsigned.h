#ifndef FWCORE_DATAFORMATS_ICUNSIGNED
#define FWCORE_DATAFORMATS_ICUNSIGNED

#include "FWCore/DataFormats/interface/ICDataType.h"

// C++ Included
#include <string>

class ICUnsigned : public ICDataType {
public:

  ICUnsigned();
  ICUnsigned(unsigned input);
  
  unsigned get();
  
protected:

  unsigned m_var;
  
};

#endif