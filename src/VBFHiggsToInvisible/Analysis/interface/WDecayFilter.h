#ifndef FWCore_Modules_WDecayFilter
#define FWCore_Modules_WDecayFilter

// HEPFW includes
// HEPFW includes
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/Dataset.h"
#include "FWCore/Modules/interface/FilterModule.h"
#include "FWCore/Parameters/interface/ParameterSet.h"

// C++ STD includes
#include <string>

namespace hepfw{
  
  /***********************************************/
  /** \brief WDecayFilter
   * 
   * WDecayFilter
   ***********************************************/
  class WDecayFilter : public hepfw::FilterModule {
  public:
    
    WDecayFilter();
    ~WDecayFilter();
    
    WDecayFilter(std::string name,hepfw::ParameterSet &pset,hepfw::Dataset &dataset);
    
    bool filter(hepfw::Event &event);

  private:
    
    bool     do_wgammafilter_;
    unsigned flavour_;
    unsigned countStatus3_;
    unsigned countDecay_e_;
    unsigned countDecay_mu_;
    unsigned countRest_;
    
  };
}

#endif 

//DECLARE_HEPFW_MODULE(hepfw::WDecayFilter);