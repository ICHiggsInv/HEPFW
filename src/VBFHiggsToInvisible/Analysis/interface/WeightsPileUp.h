#ifndef AnalysisTools_Producers_WeightsPileUp
#define AnalysisTools_Producers_WeightsPileUp

// HEPFW includes
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/Dataset.h"
#include "FWCore/Parameters/interface/ParameterSet.h"
#include "FWCore/Modules/interface/ProducerModule.h"

// ROOT includes
#include "TH1F.h"
#include "TH1D.h"
#include "TFile.h"

// C++ STD includes
#include <string>

namespace hepfw{
  
  /***********************************************/
  /** \brief WeightsPileUp 
   * 
   * WeightsPileUp
   ***********************************************/
  class WeightsPileUp : public hepfw::ProducerModule {
  public:
    
    WeightsPileUp();
    WeightsPileUp(std::string name);
    WeightsPileUp(std::string name,hepfw::ParameterSet &pset,hepfw::Dataset &dataset);
    ~WeightsPileUp();
    
    void beginJob(hepfw::JobSetup &job);
    
    void produce(hepfw::Event &event);
    
    
  private:
    
  private:
    
    bool   m_verbose;
    TH1D *m_hPUData;
    TH1D *m_hPUMC;
    TH1D *m_weights;
    
  };
}

#endif 

//DECLARE_HEPFW_MODULE(hepfw::WeightsPileUp);