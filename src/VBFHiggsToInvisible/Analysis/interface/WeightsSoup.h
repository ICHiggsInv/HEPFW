#ifndef AnalysisTools_Producers_WeightsSoup
#define AnalysisTools_Producers_WeightsSoup

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
  /** \brief WeightsSoup 
   * 
   * WeightsSoup
   ***********************************************/
  class WeightsSoup : public hepfw::ProducerModule {
  public:
    
    WeightsSoup();
    WeightsSoup(std::string name);
    WeightsSoup(std::string name,hepfw::ParameterSet &pset,hepfw::Dataset &dataset);
    ~WeightsSoup();
    
    void beginJob(hepfw::JobSetup &job);
    
    void produce(hepfw::Event &event);
    
    void SetWTargetFractions (double f0,    double f1, double f2, double f3, double f4);
    void SetWInputYields     (double n_inc, double n1, double n2, double n3, double n4);
    void SetDYTargetFractions(double zf0,   double zf1,double zf2,double zf3,double zf4);
    void SetDYInputYields    (double zn_inc,double zn1,double zn2,double zn3,double zn4);
    
  private:
    
    bool        m_verbose;
    std::string m_datasetName;
    
    bool m_do_w_soup;
    bool m_do_dy_soup;
    
    double f0_,f1_,f2_,f3_,f4_,n_inc_,n1_,n2_,n3_,n4_,w0_,w1_,w2_,w3_,w4_;
    double zf0_,zf1_,zf2_,zf3_,zf4_,zn_inc_,zn1_,zn2_,zn3_,zn4_,zw0_,zw1_,zw2_,zw3_,zw4_;
    
  };
}

#endif 

//DECLARE_HEPFW_MODULE(hepfw::WeightsSoup);