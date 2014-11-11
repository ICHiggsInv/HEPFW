#ifndef AnalysisTools_CutFlows_AnalysisCutFlow
#define AnalysisTools_CutFlows_AnalysisCutFlow

// HEPFW includes
#include "AnalysisTools/CutFlows/interface/AnalysisCut.h"
#include "FWCore/Framework/interface/Event.h"

// ROOT includes
#include "TH1D.h"
#include "TDirectory.h"

// C++ STD includes
#include <string>
#include <vector>
#include <iostream>

namespace hepfw{
  
  /***********************************************/
  /** \brief AnalysisCutFlow 
   * 
   * AnalysisCutFlow
   ***********************************************/
  class AnalysisCutFlow {
  public:
    
    AnalysisCutFlow();
    AnalysisCutFlow(std::string name);
    ~AnalysisCutFlow();
    
    void init();
    
    void setEventYieldDirectory(TDirectory* dir);
    
    std::string getName();
    
    void addAnalysisCut(hepfw::AnalysisCut* cut);
    
    bool evaluate(hepfw::Event &event);
    
    void setName(std::string name);
    
  public:
    
    std::string                      m_name;
    std::vector<hepfw::AnalysisCut*> m_cutFlow;
    
    TDirectory* m_eventYieldsDirectory;
    TH1D*       m_eventYields_Absolute;
    TH1D*       m_eventYields_Weighted;
  };
}

#endif
