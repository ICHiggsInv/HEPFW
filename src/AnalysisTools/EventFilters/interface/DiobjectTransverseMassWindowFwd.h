#ifndef AnalysisTools_EventFilters_DiobjectTransverseMassWindowFwd
#define AnalysisTools_EventFilters_DiobjectTransverseMassWindowFwd

// HEPFW includes
#include "AnalysisTools/EventFilters/interface/DiobjectTransverseMassWindow.h"

// ICHiggsTauTau
#include "DataFormats/ICHiggsTauTau/interface/Met.h"
#include "DataFormats/ICHiggsTauTau/interface/Tau.h"

namespace hepfw{
  
  typedef hepfw::DiobjectTransverseMassWindow<ic::Met,ic::Tau> DiobjectTransverseMassWindow_MET_Tau;

}

#endif 

//DECLARE_HEPFW_MODULE(hepfw::DiobjectTransverseMassWindow_MET_Tau);
