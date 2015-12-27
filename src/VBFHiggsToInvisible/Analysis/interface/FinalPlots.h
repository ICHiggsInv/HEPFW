#ifndef AnalysisTools_Plots_FinalPlots
#define AnalysisTools_Plots_FinalPlots

// HEPFW includes
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/Dataset.h"
#include "FWCore/Modules/interface/AnalyserModule.h"
#include "FWCore/Parameters/interface/ParameterSet.h"

// ROOT includes
#include "TH1D.h"

// C++ STD includes
#include <string>
#include <vector>

namespace hepfw{
  
  /***********************************************/
  /** \brief FinalPlots 
   * 
   * FinalPlots
   ***********************************************/
  class FinalPlots : public hepfw::AnalyserModule {
  public:
    
    FinalPlots();
    FinalPlots(std::string name);
    FinalPlots(std::string name,hepfw::ParameterSet &pset,hepfw::Dataset &dataset);
    ~FinalPlots();
    
    void analyse(hepfw::Event &event);
    
    void beginJob(hepfw::JobSetup &job);
    void endJob();
    
  private:
    
    void init();
    
  private:
    
    bool m_verbose;
    
    TH1D* m_sigRegion_metNoMuon;
    TH1D* m_sigRegion_metNoMuon_Sig;
    TH1D* m_sigRegion_Dijet_DeltaEta;
    TH1D* m_sigRegion_Dijet_Mjj;

    TH1D* m_sigZmumu_metNoMuon;
    TH1D* m_sigZmumu_metNoMuon_Sig;
    TH1D* m_sigZmumu_Dijet_DeltaEta;
    TH1D* m_sigZmumu_Dijet_Mjj;

    TH1D* m_sigWel_Dijet_Mjj;
    TH1D* m_sigWel_metNoMuon;
    TH1D* m_sigWel_MinDeltaPhiMetAllJets;
    
    TH1D* m_sigWmu_Dijet_Mjj;
    TH1D* m_sigWmu_metNoMuon;
    TH1D* m_sigWmu_MinDeltaPhiMetAllJets;
    
    TH1D* m_sigWta_Dijet_Mjj;
    TH1D* m_sigWta_metNoMuon;
    TH1D* m_sigWta_MinDeltaPhiMetAllJets;
    
  };
}

#endif 

//DECLARE_HEPFW_MODULE(hepfw::FinalPlots);
