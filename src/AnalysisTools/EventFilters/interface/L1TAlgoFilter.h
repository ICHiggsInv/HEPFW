#ifndef AnalysisTools_CutFlows_L1TAlgoFilter
#define AnalysisTools_CutFlows_L1TAlgoFilter

// HEPFW includes
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Modules/interface/FilterModule.h"

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
  class L1TAlgoFilter : public hepfw::FilterModule {
  public:
    
    L1TAlgoFilter();
    L1TAlgoFilter(std::string name);
    ~L1TAlgoFilter();
    
    void addAlgo(std::string algoName,int firstRun=1,int lastRun=10e9);
    
    bool filter(hepfw::Event &event);
    
  private:
    
  public:
    
    std::map<std::string,std::pair<int,int>> m_l1tAlgo;
    
  };
  
}

#endif 