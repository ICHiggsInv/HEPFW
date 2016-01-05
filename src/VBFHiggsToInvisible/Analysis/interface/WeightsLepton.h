#ifndef AnalysisTools_Producers_WeightsLepton
#define AnalysisTools_Producers_WeightsLepton

// HEPFW includes
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/Dataset.h"
#include "FWCore/Parameters/interface/ParameterSet.h"
#include "FWCore/Modules/interface/ProducerModule.h"

// ICHiggsTauTau
#include "DataFormats/ICHiggsTauTau/interface/Electron.h"
#include "DataFormats/ICHiggsTauTau/interface/Muon.h"

// ROOT includes
#include "TF1.h"
#include "TH1F.h"
#include "TH1D.h"
#include "TFile.h"

// C++ STD includes
#include <string>

namespace hepfw{
  
  /***********************************************/
  /** \brief WeightsLepton 
   * 
   * WeightsLepton
   ***********************************************/
  class WeightsLepton : public hepfw::ProducerModule {
  public:
    
    WeightsLepton();
    WeightsLepton(std::string name);
    WeightsLepton(std::string name,hepfw::ParameterSet &pset,hepfw::Dataset &dataset);
    ~WeightsLepton();
    
    void beginJob(hepfw::JobSetup &job);
    
    void produce(hepfw::Event &event);
    
    void     fillVector(const std::string & aFileName, std::vector<double> & aVector);
    unsigned findElectronPtEtaBin(double pt, double eta);
    unsigned findMuonPtEtaBin(double pt, double eta);
    
  private:
    
    bool        m_verbose;
    bool        m_do_idiso_tight_weights;
    bool        m_do_idiso_veto_weights;
    std::string m_datasetName;
    
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

//DECLARE_HEPFW_MODULE(hepfw::WeightsLepton);