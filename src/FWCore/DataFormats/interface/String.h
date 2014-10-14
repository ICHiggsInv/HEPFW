#ifndef FWCORE_DATAFORMATS_STRING
#define FWCORE_DATAFORMATS_STRING

#include "FWCore/DataFormats/interface/DataType.h"

// C++ Included
#include <string>

namespace hepfw{
  
  /***********************************************/
  /** \brief String
   * 
   * String
   ***********************************************/ 
  class String : public hepfw::DataType {
  public:
    
    String();
    String(std::string input);
    
    std::string get();
    
  protected:
    
    std::string m_var;
    
  };
  
}

#endif