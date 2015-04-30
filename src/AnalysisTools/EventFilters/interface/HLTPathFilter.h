#ifndef AnalysisTools_CutFlows_HLTPathFilter
#define AnalysisTools_CutFlows_HLTPathFilter

// HEPFW includes
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Modules/interface/FilterModule.h"
#include "FWCore/Parameters/interface/ParameterSet.h"

// C++ STD includes
#include <string>
#include <utility>
#include <map>

namespace hepfw{
  
  /***********************************************/
  /** \brief HLT Path Filter
   * 
   * 
   ***********************************************/
  class HLTPathFilter : public hepfw::FilterModule {
  public:
    
    HLTPathFilter();
    HLTPathFilter(std::string name);
    HLTPathFilter(std::string name,hepfw::ParameterSet &pset);
    ~HLTPathFilter();
    
    void addPath(std::string hltAlgo,int firstRun=1,int lastRun=10e9);
    
    bool filter(hepfw::Event &event);
    
  private:
    
    void init();
    
  private:
    
    bool                                           m_verbose;
    std::multimap<std::string,std::pair<int,int> > m_hltPaths;
    
  };
  
}

#endif 

//DECLARE_HEPFW_MODULE(hepfw::HLTPathFilter);
