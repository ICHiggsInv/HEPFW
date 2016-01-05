#ifndef FWCore_Modules_ZDecayFilter
#define FWCore_Modules_ZDecayFilter

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
  /** \brief ZDecayFilter
   * 
   * ZDecayFilter
   ***********************************************/
  class ZDecayFilter : public hepfw::FilterModule {
  public:
    
    ZDecayFilter();
    ~ZDecayFilter();
    
    ZDecayFilter(std::string name,hepfw::ParameterSet &pset,hepfw::Dataset &dataset);
    
    bool filter(hepfw::Event &event);
    
  private:
    
    unsigned flavour_;
    
    bool doFilter;
    unsigned countStatus3_;
    double minMll_;
    double maxMll_;
    bool doptinstead_;
    
  };
}

#endif 

//DECLARE_HEPFW_MODULE(hepfw::ZDecayFilter);