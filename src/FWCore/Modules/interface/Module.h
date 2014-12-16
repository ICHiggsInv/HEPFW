#ifndef FWCore_Modules_Module
#define FWCore_Modules_Module

// HEPFW includes
#include "FWCore/Framework/interface/JobSetup.h"
#include "FWCore/Parameters/interface/ParameterSet.h"

// C++ STD includes
#include <string>

namespace hepfw{
  
  /***********************************************/
  /** \brief Module
   * 
   * Module
   ***********************************************/
  class Module {
  public:

    enum ModuleType{
      Generic,
      Analyser,
      Filter,
      Producer
    };
    
    Module();
    Module(std::string name);
    Module(std::string name,hepfw::ParameterSet pset);
    ~Module();
    
    std::string                       getName();
    virtual hepfw::Module::ModuleType getType();

    virtual void beginJob(hepfw::JobSetup &job);
    virtual void endJob();
    
  protected:
    
    std::string               m_name;
    hepfw::Module::ModuleType m_type;
    
  };
}

#endif 