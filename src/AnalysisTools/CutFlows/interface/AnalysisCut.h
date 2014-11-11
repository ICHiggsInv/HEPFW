#ifndef AnalysisTools_CutFlows_AnalysisCut
#define AnalysisTools_CutFlows_AnalysisCut

// HEPFW includes
#include "FWCore/Framework/interface/Event.h"

// C++ STD includes
#include <string>

namespace hepfw{
  
  /***********************************************/
  /** \brief AnalysisCut 
   * 
   * AnalysisCut
   ***********************************************/
  class AnalysisCut {
  public:
    
    AnalysisCut();
    AnalysisCut(std::string name);
    ~AnalysisCut();
    
    bool evaluate(hepfw::Event &event);
    
    std::string getName();
    
  public:
    
    std::string m_name;
    
  };

}

#endif 
