#ifndef FWCORE_DATAFORMATS_FLOAT
#define FWCORE_DATAFORMATS_FLOAT

#include "FWCore/DataFormats/interface/DataType.h"

// C++ Included
#include <string>

namespace hepfw{
  
  /***********************************************/
  /** \brief Float
   * 
   * Float
   ***********************************************/ 
  class Float : public hepfw::DataType {
  public:
    
    Float();
    Float(float input);
    
    float get();
    
  protected:
    
    float m_var;
    
  };
  
}

#endif