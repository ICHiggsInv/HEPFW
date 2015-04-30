#ifndef FWCore_Modules_ProducerModule
#define FWCore_Modules_ProducerModule

// HEPFW includes
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Modules/interface/Module.h"

// C++ STD includes
#include <string>

namespace hepfw{
  
  /***********************************************/
  /** \brief ProducerModule
   * 
   * ProducerModule
   ***********************************************/
  class ProducerModule : public hepfw::Module {
  public:
    
    ProducerModule();
    ~ProducerModule();
    
    virtual void produce(hepfw::Event &event);
    
  private:
    
  };
}

#endif 