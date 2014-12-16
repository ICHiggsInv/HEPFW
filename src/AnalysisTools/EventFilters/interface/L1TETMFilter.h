#ifndef AnalysisTools_CutFlows_L1TETM
#define AnalysisTools_CutFlows_L1TETM

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
  class L1TETMFilter : public hepfw::FilterModule {
  public:
    
    L1TETMFilter();
    L1TETMFilter(std::string name);
    L1TETMFilter(std::string name,hepfw::ParameterSet &pset);
    ~L1TETMFilter();
    
    bool filter(hepfw::Event &event);
    
    void setMinL1TETM(double value);
    
  private:
    
    void init();
    
  private:

    bool   m_verbose;
    double m_minL1TETM;
    
  };
  
}

#endif 

//DECLARE_HEPFW_MODULE(hepfw::L1TETMFilter);
