#ifndef FWCORE_DATAFORMATS_ICSTRING
#define FWCORE_DATAFORMATS_ICSTRING

#include "FWCore/DataFormats/interface/ICDataType.h"

// C++ Included
#include <string>

class ICString : public ICDataType {
public:

  ICString();
  ICString(std::string input);
  
  std::string get();
  
protected:

  std::string m_var;
  
};

#endif