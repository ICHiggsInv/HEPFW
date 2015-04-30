#ifndef AnalysisTools_CutFlows_EDMFilterFilter
#define AnalysisTools_CutFlows_EDMFilterFilter

// HEPFW includes
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/JobSetup.h"
#include "FWCore/Modules/interface/FilterModule.h"
#include "FWCore/Parameters/interface/ParameterSet.h"

// ICHiggsTauTau
#include "DataFormats/ICHiggsTauTau/interface/Met.h"

// ROOT includes
#include "TH1D.h"

// C++ STD includes
#include <string>
#include <map>

namespace hepfw{
  
  /***********************************************/
  /** \brief EDM Filter Filter 
   * 
   * This class will filter an event out if any of the user defined
   * EDM filters if found on the event in the defined state.
   ***********************************************/
  class EDMFilterFilter : public hepfw::FilterModule {
  public:
    
    EDMFilterFilter();
    EDMFilterFilter(std::string name);
    EDMFilterFilter(std::string name,hepfw::ParameterSet &pset);
    ~EDMFilterFilter();
    
    void addFilter(std::string filterName, bool resultTofilter=false);
    
    bool filter(hepfw::Event &event);
    
    void beginJob(hepfw::JobSetup &job);
    void endJob();
    
  private:
    
    void init();
    
  private:
    
    bool m_verbose;
    
    std::map<std::string,bool> m_edmFilters;
    TH1D*                      m_filterCount;
  };

}

#endif 

//DECLARE_HEPFW_MODULE(hepfw::EDMFilterFilter);
