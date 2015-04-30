#ifndef FWCore_Modules_ModuleSequence
#define FWCore_Modules_ModuleSequence

// HEPFW includes
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Modules/interface/Module.h"

// ROOT includes
#include "TH1D.h"
#include "TDirectory.h"

// C++ STD includes
#include <string>

namespace hepfw{
  
  /***********************************************/
  /** \brief ModuleSequence
   * 
   * ModuleSequence
   ***********************************************/
  class ModuleSequence {
  public:
    
    ModuleSequence();
    ModuleSequence(std::string name);
    ~ModuleSequence();
    
    void init();
    
    bool execute(hepfw::Event &event);

    void addModule(hepfw::Module *module);
    
    void setName               (std::string);
    void setTitle              (std::string);
    void setEventYieldDirectory(TDirectory* dir);
    
    std::string                 getName();
    std::vector<hepfw::Module*> getSequence();
    
  private:
    
    std::string                 m_name;
    std::string                 m_title;
    std::vector<hepfw::Module*> m_modules;
    
    TDirectory *m_eventYieldsDirectory;
    TH1D       *m_eventYields_Absolute;
    TH1D       *m_eventYields_Weighted;
    
  };
}

#endif  
