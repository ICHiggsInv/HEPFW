#ifndef FWCORE_DATAFORMATS_ICFLOAT
#define FWCORE_DATAFORMATS_ICFLOAT

#include "FWCore/DataFormats/interface/ICDataType.h"

// C++ Included
#include <string>

class ICFloat : public ICDataType {
public:

  ICFloat();
  ICFloat(float input);
  
  float get();
  
protected:

  float m_var;
  
};

#endif