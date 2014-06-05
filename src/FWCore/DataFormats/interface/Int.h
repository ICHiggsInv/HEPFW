#ifndef FWCORE_DATAFORMATS_INT
#define FWCORE_DATAFORMATS_INT

#include "FWCore/DataFormats/interface/DataType.h"

// C++ Included
#include <string>

namespace rat{
  
  /***********************************************/
  /** \brief Int
   * 
   * Int
   ***********************************************/ 
  class Int : public rat::DataType {
  public:
    
    Int();
    Int(int input);
    
    int get();
    
  protected:
    
    int m_var;
    
  };
  
}

#endif