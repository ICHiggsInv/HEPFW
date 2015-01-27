#ifndef AnalysisTools_Filters_CollectionSizeFilterFwd
#define AnalysisTools_Filters_CollectionSizeFilterFwd

// HEPFW includes
#include "AnalysisTools/Filters/interface/CollectionSizeFilter.h"

// ICHiggsTauTau
#include "DataFormats/ICHiggsTauTau/interface/Electron.h"
#include "DataFormats/ICHiggsTauTau/interface/Muon.h"
#include "DataFormats/ICHiggsTauTau/interface/Tau.h"

namespace hepfw{
  
  typedef hepfw::CollectionSizeFilter<ic::Electron> ColSizeFilterElectron;
  typedef hepfw::CollectionSizeFilter<ic::Muon>     ColSizeFilterMuon;
  typedef hepfw::CollectionSizeFilter<ic::Tau>      ColSizeFilterTau;
  
}

#endif 

//DECLARE_HEPFW_MODULE(hepfw::ColSizeFilterElectron);
//DECLARE_HEPFW_MODULE(hepfw::ColSizeFilterMuon);
//DECLARE_HEPFW_MODULE(hepfw::ColSizeFilterTau);
