#ifndef AnalysisTools_Filters_OverlapCleaningFwd
#define AnalysisTools_Filters_OverlapCleaningFwd

// HEPFW includes
#include "AnalysisTools/CollectionFilters/interface/OverlapCleaning.h"

namespace hepfw{
 
  typedef hepfw::OverlapCleaning<ic::PFJet,ic::Electron> OverlapCleaning_PFJet_Electron;
  typedef hepfw::OverlapCleaning<ic::PFJet,ic::Muon>     OverlapCleaning_PFJet_Muon;
  typedef hepfw::OverlapCleaning<ic::Electron,ic::Muon>  OverlapCleaning_Electron_Muon;
}
  
#endif  

//DECLARE_HEPFW_MODULE(hepfw::OverlapCleaning_PFJet_Electron);
//DECLARE_HEPFW_MODULE(hepfw::OverlapCleaning_PFJet_Muon);
//DECLARE_HEPFW_MODULE(hepfw::OverlapCleaning_Electron_Muon);
