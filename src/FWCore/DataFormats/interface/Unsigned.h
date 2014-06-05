#ifndef FWCORE_DATAFORMATS_UNSIGNED
#define FWCORE_DATAFORMATS_UNSIGNED

#include "FWCore/DataFormats/interface/DataType.h"

// C++ Included
#include <string>

namespace rat{
  
  /***********************************************/
  /** \brief Unsigned
   * 
   * Unsigned
   ***********************************************/ 
  class Unsigned : public rat::DataType {
  public:
    
    Unsigned();
    Unsigned(unsigned input);
    
    unsigned get();
    
  protected:
    
    unsigned m_var;
    
  };
  
}

#endif