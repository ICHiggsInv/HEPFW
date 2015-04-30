#ifndef AnalysisTools_Plots_RegionAnalysis_QCD
#define AnalysisTools_Plots_RegionAnalysis_QCD

// HEPFW includes
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Modules/interface/AnalyserModule.h"
#include "FWCore/Parameters/interface/ParameterSet.h"

// ROOT includes
#include "TH1D.h"

// C++ STD includes
#include <string>
#include <vector>
#include <map>

namespace hepfw{
  
  /***********************************************/
  /** \brief RegionAnalysis_QCD 
   * 
   * RegionAnalysis_QCD
   ***********************************************/
  class RegionAnalysis_QCD : public hepfw::AnalyserModule {
  public:
    
    RegionAnalysis_QCD();
    RegionAnalysis_QCD(std::string name);
    RegionAnalysis_QCD(std::string name,hepfw::ParameterSet &pset);
    ~RegionAnalysis_QCD();
    
    void analyse(hepfw::Event &event);
    
    void beginJob(hepfw::JobSetup &job);
    void endJob();
    
  private:
    
    void init();
    
  private:
    
    bool m_verbose;
    
    std::string m_labelMet;
    std::string m_labelJets;
    
    TH1D* m_hEntries;
    
    std::map<std::string,TH1D*> m_hBase;
    std::map<std::string,TH1D*> m_hQCD;
    std::map<std::string,TH1D*> m_hNorm1;
    std::map<std::string,TH1D*> m_hNorm2;
    std::map<std::string,TH1D*> m_hNorm3;
    std::map<std::string,TH1D*> m_hSignal;
    
  };
}

#endif 

//DECLARE_HEPFW_MODULE(hepfw::RegionAnalysis_QCD);
