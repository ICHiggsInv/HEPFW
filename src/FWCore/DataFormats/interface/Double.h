#ifndef FWCORE_DATAFORMATS_DOUBLE
#define FWCORE_DATAFORMATS_DOUBLE

#include "FWCore/DataFormats/interface/DataType.h"

// C++ Included
#include <string>

namespace rat{
  
  /***********************************************/
  /** \brief Double
   * 
   * Double
   ***********************************************/ 
  class Double : public rat::DataType {
  public:
    
    Double();
    Double(double input);
    
    double get();
    
  protected:
    
    double m_var;
    
  };
  
}

#endif