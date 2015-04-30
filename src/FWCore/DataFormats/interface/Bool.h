#ifndef FWCORE_DATAFORMATS_BOOL
#define FWCORE_DATAFORMATS_BOOL

#include "FWCore/DataFormats/interface/DataType.h"

// C++ Included
#include <string>

namespace hepfw{
  
  /***********************************************/
  /** \brief Bool
   * 
   * Bool
   ***********************************************/ 
  class Bool : public hepfw::DataType {
  public:
    
    Bool();
    Bool(bool input);
    
    bool get();
    
  protected:
    
    bool m_var;
    
  };

}

#endif