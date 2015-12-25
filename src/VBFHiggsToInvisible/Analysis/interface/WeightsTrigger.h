#ifndef AnalysisTools_Producers_WeightsTrigger
#define AnalysisTools_Producers_WeightsTrigger

// HEPFW includes
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/Dataset.h"
#include "FWCore/Parameters/interface/ParameterSet.h"
#include "FWCore/Modules/interface/ProducerModule.h"

// ROOT includes
#include "TF1.h"
#include "TH1F.h"
#include "TH1D.h"
#include "TFile.h"

// C++ STD includes
#include <string>

namespace hepfw{
  
  /***********************************************/
  /** \brief WeightsTrigger 
   * 
   * WeightsTrigger
   ***********************************************/
  class WeightsTrigger : public hepfw::ProducerModule {
  public:
    
    WeightsTrigger();
    WeightsTrigger(std::string name);
    WeightsTrigger(std::string name,hepfw::ParameterSet &pset,hepfw::Dataset &dataset);
    ~WeightsTrigger();
    
    void beginJob(hepfw::JobSetup &job);
    
    void produce(hepfw::Event &event);
    
    
  private:
    
  private:
    
    bool   m_verbose;
    TFile *triggerSF_;
    
    std::vector<std::vector<std::vector<TF1*> > > func_trigSF_binnedin2d;
    std::vector<std::string> binnedin2d1dfitweightvarorder_;
    std::vector<double> binnedin2d1dfitweightvar1binning_;
    std::vector<double> binnedin2d1dfitweightvar2binning_;
    
  };
}

#endif 

//DECLARE_HEPFW_MODULE(hepfw::WeightsTrigger);