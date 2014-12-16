#ifndef AnalysisTools_CutFlows_AnalysisCutMet
#define AnalysisTools_CutFlows_AnalysisCutMet

// HEPFW includes
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Modules/interface/FilterModule.h"

// ICHiggsTauTau
#include "DataFormats/ICHiggsTauTau/interface/Met.h"

// C++ STD includes
#include <string>

namespace hepfw{
  
  /***********************************************/
  /** \brief AnalysisCutMet 
   * 
   * AnalysisCutMet
   ***********************************************/
  class AnalysisCutMet : public hepfw::FilterModule {
  public:
    
    AnalysisCutMet();
    AnalysisCutMet(std::string name);
    AnalysisCutMet(std::string name,hepfw::ParameterSet &pset);
    ~AnalysisCutMet();
    
    bool filter(hepfw::Event &event);
    
    void setMetCollection(std::string metLabel);
    
    void setMinMet            (double met);
    void setMinMetSignificance(double metSig);
    
  private:
    
    void init();
    
  public:
    
    bool m_verbose;
    
    std::string m_metLabel;
    
    double m_minMet;
    double m_minMetSig;
  };

}

#endif 

//DECLARE_HEPFW_MODULE(hepfw::AnalysisCutMet);
