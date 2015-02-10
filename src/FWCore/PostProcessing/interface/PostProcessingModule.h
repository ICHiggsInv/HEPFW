#ifndef FWCore_PostProcessing_PostProcessingPostProcessingModule
#define FWCore_PostProcessing_PostProcessingPostProcessingModule

// HEPFW includes
#include "FWCore/Framework/interface/JobSetup.h"
#include "FWCore/Parameters/interface/ParameterSet.h"

// C++ STD includes
#include <string>

namespace hepfw{
  
  /***********************************************/
  /** \brief PostProcessingModule
   * 
   * PostProcessingModule
   ***********************************************/
  class PostProcessingModule {
  public:
    
    PostProcessingModule();
    PostProcessingModule(std::string name);
    PostProcessingModule(std::string name,hepfw::ParameterSet pset);
    ~PostProcessingModule();
    
    std::string getName();
    
    virtual void process();
    
  protected:
    
    std::string m_name;
    
  };
}

#endif 