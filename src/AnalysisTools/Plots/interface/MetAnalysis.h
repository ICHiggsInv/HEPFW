#ifndef AnalysisTools_Plots_MetAnalysis
#define AnalysisTools_Plots_MetAnalysis

// HEPFW includes
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Modules/interface/AnalyserModule.h"
#include "FWCore/Parameters/interface/ParameterSet.h"

// ROOT includes
#include "TH1D.h"

// C++ STD includes
#include <string>
#include <vector>

namespace hepfw{
  
  /***********************************************/
  /** \brief MetAnalysis 
   * 
   * MetAnalysis
   ***********************************************/
  class MetAnalysis : public hepfw::AnalyserModule {
  public:
    
    MetAnalysis();
    MetAnalysis(std::string name);
    MetAnalysis(std::string name,hepfw::ParameterSet &pset);
    ~MetAnalysis();
    
    void analyse(hepfw::Event &event);
    
    void beginJob(hepfw::JobSetup &job);
    void endJob();
    
  private:
    
    void init();
    
  private:
    
    bool m_verbose;
    
    std::string m_labelMet;
    std::string m_labelMetNoMuon;
    std::string m_labelMuonsLoose;
    std::string m_labelMuonsTight;
    
    TH1D* m_met;
    TH1D* m_metNoMuon;
    TH1D* m_met_Sig;
    TH1D* m_metNoMuon_Sig;
    
    TH1D* m_muonsLoose_multiplicity;
    TH1D* m_muonsTight_multiplicity;
    
  };
}

#endif 

//DECLARE_HEPFW_MODULE(hepfw::MetAnalysis);
