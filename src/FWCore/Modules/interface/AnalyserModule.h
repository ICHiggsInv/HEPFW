#ifndef FWCore_Modules_AnalyserModule
#define FWCore_Modules_AnalyserModule

// HEPFW includes
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Modules/interface/Module.h"

// C++ STD includes
#include <string>

namespace hepfw{
  
  /***********************************************/
  /** \brief AnalyserModule
   * 
   * AnalyserModule
   ***********************************************/
  class AnalyserModule : public hepfw::Module {
  public:
    
    AnalyserModule();
    ~AnalyserModule();
    
    virtual void analyse(hepfw::Event &event);
    
  private:
    
  };
}

#endif 