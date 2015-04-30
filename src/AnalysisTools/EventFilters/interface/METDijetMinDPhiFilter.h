#ifndef AnalysisTools_CutFlows_METDijetMinDPhiFilter
#define AnalysisTools_CutFlows_METDijetMinDPhiFilter

// HEPFW includes
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Modules/interface/FilterModule.h"

// C++ STD includes
#include <string>
#include <map>

namespace hepfw{
  
  /***********************************************/
  /** \brief METDijetMinDPhiFilter
   * 
   * 
   ***********************************************/
  class METDijetMinDPhiFilter : public hepfw::FilterModule {
  public:
    
    METDijetMinDPhiFilter();
    METDijetMinDPhiFilter(std::string name);
    METDijetMinDPhiFilter(std::string name,hepfw::ParameterSet &pset);
    ~METDijetMinDPhiFilter();
    
    bool filter(hepfw::Event &event);
    
    void setMinDPhi      (double minDPhi);
    void setJetCollection(std::string jetsLabel);
    void setMetCollection(std::string metLabel);
    
  private:
    
    void init();
    
  private:
    
    bool m_verbose;
    
    std::string m_metLabel;
    std::string m_jetsLabel;
    double      m_minDPhi;
    
  };
  
}

#endif 

//DECLARE_HEPFW_MODULE(hepfw::METDijetMinDPhiFilter);
