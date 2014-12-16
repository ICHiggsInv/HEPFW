#ifndef AnalysisTools_CutFlows_METJetsMinDPhiFilter
#define AnalysisTools_CutFlows_METJetsMinDPhiFilter

// HEPFW includes
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Modules/interface/FilterModule.h"

// C++ STD includes
#include <string>
#include <map>

namespace hepfw{
  
  /***********************************************/
  /** \brief HLT Path Filter
   * 
   * 
   ***********************************************/
  class METJetsMinDPhiFilter : public hepfw::FilterModule {
  public:
    
    METJetsMinDPhiFilter();
    METJetsMinDPhiFilter(std::string name);
    METJetsMinDPhiFilter(std::string name,hepfw::ParameterSet &pset);
    ~METJetsMinDPhiFilter();
    
    bool filter(hepfw::Event &event);
    
    void setMinJetPt     (double minPt);
    void setMinDPhi      (double minDPhi);
    void setJetCollection(std::string jetsLabel);
    void setMetCollection(std::string metLabel);
    
  private:
    
    void init();
    
  private:
    
    bool m_verbose;
    
    std::string m_metLabel;
    std::string m_jetsLabel;
    double      m_minJetPt;
    double      m_minDPhi;
    
  };
  
}

#endif 

//DECLARE_HEPFW_MODULE(hepfw::METJetsMinDPhiFilter);
