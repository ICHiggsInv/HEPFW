#ifndef AnalysisTools_Producers_WeightsTop
#define AnalysisTools_Producers_WeightsTop

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
  /** \brief WeightsTop 
   * 
   * WeightsTop
   ***********************************************/
  class WeightsTop : public hepfw::ProducerModule {
  public:
    
    WeightsTop();
    WeightsTop(std::string name);
    WeightsTop(std::string name,hepfw::ParameterSet &pset,hepfw::Dataset &dataset);
    ~WeightsTop();
    
    void beginJob(hepfw::JobSetup &job);
    
    void produce(hepfw::Event &event);
    
  private:
    
    bool        m_verbose;
    std::string m_datasetName;
    
  };
}

#endif 

//DECLARE_HEPFW_MODULE(hepfw::WeightsTop);