#ifndef AnalysisTools_CutFlows_EventListFilter
#define AnalysisTools_CutFlows_EventListFilter

// HEPFW includes
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/JobSetup.h"
#include "FWCore/Modules/interface/FilterModule.h"
#include "FWCore/Parameters/interface/ParameterSet.h"

// C++ STD includes
#include <string>
#include <set>
#include <map>

namespace hepfw{
  
  /***********************************************/
  /** \brief EventListFilter
   * 
   ***********************************************/
  class EventListFilter : public hepfw::FilterModule {
  public:
    
    EventListFilter();
    EventListFilter(std::string name);
    EventListFilter(std::string name,hepfw::ParameterSet &pset);
    ~EventListFilter();
    
    void beginJob(hepfw::JobSetup &job);
    
    bool filter(hepfw::Event &event);
    
    void setEventFilelist(std::string filePath);
    
  private:
    
    void init();
    
  private:
    
    bool m_verbose;
    
    std::string                                 m_filePath;
    std::map<int,std::map<int,std::set<unsigned> > > m_events;
    
  };
  
}

#endif 

//DECLARE_HEPFW_MODULE(hepfw::EventListFilter);
