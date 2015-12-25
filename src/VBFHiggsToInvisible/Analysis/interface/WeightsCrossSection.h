#ifndef AnalysisTools_Producers_WeightsCrossSection
#define AnalysisTools_Producers_WeightsCrossSection

// HEPFW includes
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/Dataset.h"
#include "FWCore/Parameters/interface/ParameterSet.h"
#include "FWCore/Modules/interface/ProducerModule.h"

// ROOT includes
#include "TH1F.h"
#include "TFile.h"

// C++ STD includes
#include <string>

namespace hepfw{
  
  /***********************************************/
  /** \brief WeightsCrossSection 
   * 
   * WeightsCrossSection
   ***********************************************/
  class WeightsCrossSection : public hepfw::ProducerModule {
  public:
    
    WeightsCrossSection();
    WeightsCrossSection(std::string name);
    WeightsCrossSection(std::string name,hepfw::ParameterSet &pset,hepfw::Dataset &dataset);
    ~WeightsCrossSection();
    
    void beginJob(hepfw::JobSetup &job);
    
    void produce(hepfw::Event &event);
    
    void SetWTargetFractions (double f0,    double f1, double f2, double f3, double f4);
    void SetWInputYields     (double n_inc, double n1, double n2, double n3, double n4);
    void SetDYTargetFractions(double zf0,   double zf1,double zf2,double zf3,double zf4);
    void SetDYInputYields    (double zn_inc,double zn1,double zn2,double zn3,double zn4);
    
  private:
    
  private:
    
    bool   m_verbose;
    bool   m_do_w_soup;
    
    double m_weightXSec;
    
    TFile *triggerSF_;
    TH1F  *hist_trigSF_METL1;
    TH1F  *hist_trigSF_METHLT;
    TH1F  *hist_trigSF_MjjHLT;
    TH1F  *hist_trigSF_JetHLT;
    
    TH1F* tighteleweight;
    TH1F* tightmuweight;
    TH1F* vetoeleweight;
    TH1F* vetomuweight;
    
    std::vector<double> eTight_idisoSF_;
    std::vector<double> eVeto_idisoDataEff_;
    std::vector<double> eVeto_idisoMCEff_;
    std::vector<double> muTight_idSF_;
    std::vector<double> muTight_isoSF_;
    std::vector<double> muVeto_idDataEff_;
    std::vector<double> muVeto_isoDataEff_;
    std::vector<double> muVeto_idMCEff_;
    std::vector<double> muVeto_isoMCEff_;
    std::vector<double> muTight_idisoSF_;
    std::vector<double> muVeto_idisoDataEff_;
    std::vector<double> muVeto_idisoMCEff_;
    
    double f0_,f1_,f2_,f3_,f4_,n_inc_,n1_,n2_,n3_,n4_,w0_,w1_,w2_,w3_,w4_;
    double zf0_,zf1_,zf2_,zf3_,zf4_,zn_inc_,zn1_,zn2_,zn3_,zn4_,zw0_,zw1_,zw2_,zw3_,zw4_;
    
    unsigned eventsWithGenElectron_;
    unsigned eventsWithGenMuon_;
    unsigned eventsWithGenTau_;
    unsigned eventsWithGenElectronFromTau_;
    unsigned eventsWithGenMuonFromTau_;
    unsigned eventsWithGenElectronInAcc_;
    unsigned eventsWithGenMuonInAcc_;
    unsigned eventsWithGenElectronFromTauInAcc_;
    unsigned eventsWithGenMuonFromTauInAcc_;
    
    
  };
}

#endif 

//DECLARE_HEPFW_MODULE(hepfw::WeightsCrossSection);