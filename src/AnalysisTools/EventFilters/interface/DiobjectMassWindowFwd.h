#ifndef AnalysisTools_EventFilters_DiobjectMassWindowFwd
#define AnalysisTools_EventFilters_DiobjectMassWindowFwd

// HEPFW includes
#include "AnalysisTools/EventFilters/interface/DiobjectMassWindow.h"

// ICHiggsTauTau
#include "DataFormats/ICHiggsTauTau/interface/Muon.h"

namespace hepfw{
  
  typedef hepfw::DiobjectMassWindow<ic::Muon> DimuonMassWindow;

}

#endif 

//DECLARE_HEPFW_MODULE(hepfw::DimuonMassWindow);
