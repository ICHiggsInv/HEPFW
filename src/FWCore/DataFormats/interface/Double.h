#ifndef FWCORE_DATAFORMATS_ICDOUBLE
#define FWCORE_DATAFORMATS_ICDOUBLE

#include "FWCore/DataFormats/interface/ICDataType.h"

// C++ Included
#include <string>

class ICDouble : public ICDataType {
public:

  ICDouble();
  ICDouble(double input);
  
  double get();
  
protected:

  double m_var;
  
};

#endif