#ifndef FWCore_PostProcessing_PostProcessingModule
#define FWCore_PostProcessing_PostProcessingModule

// HEPFW includes
#include "FWCore/Parameters/interface/ParameterSet.h"
#include "PostProcessing/Data/interface/ProcessedDataManager.h"

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
    
    virtual void process(hepfw::ProcessedDataManager& data);
    
  protected:
    
    std::string m_name;
    
  };
}

#endif 