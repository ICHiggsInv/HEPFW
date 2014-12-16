#ifndef FWCore_Modules_FilterModule
#define FWCore_Modules_FilterModule

// HEPFW includes
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Modules/interface/Module.h"

// C++ STD includes
#include <string>

namespace hepfw{
  
  /***********************************************/
  /** \brief FilterModule
   * 
   * FilterModule
   ***********************************************/
  class FilterModule : public hepfw::Module {
  public:
    
    FilterModule();
    ~FilterModule();
    
    virtual bool filter(hepfw::Event &event);
    
  private:
    
  };
}

#endif 