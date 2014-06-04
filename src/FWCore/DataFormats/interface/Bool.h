#ifndef FWCORE_DATAFORMATS_ICBOOL
#define FWCORE_DATAFORMATS_ICBOOL

#include "FWCore/DataFormats/interface/ICDataType.h"

// C++ Included
#include <string>

class ICBool : public ICDataType {
public:

  ICBool();
  ICBool(bool input);
  
  bool get();
  
protected:

  bool m_var;
  
};

#endif