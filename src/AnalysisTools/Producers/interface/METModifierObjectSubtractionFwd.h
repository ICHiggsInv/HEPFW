#ifndef AnalysisTools_Producers_METModifierObjectSubtractionFwd
#define AnalysisTools_Producers_METModifierObjectSubtractionFwd

// HEPFW includes
#include "AnalysisTools/Producers/interface/METModifierObjectSubtraction.h"

// ICHiggsTauTau
#include "DataFormats/ICHiggsTauTau/interface/Met.h"
#include "DataFormats/ICHiggsTauTau/interface/Muon.h"

namespace hepfw{
  
  typedef hepfw::METModifierObjectSubtraction<ic::Met,ic::Muon> MetModifier_MuonSubtraction;
  
}

#endif 

//DECLARE_HEPFW_MODULE(hepfw::MetModifier_MuonSubtraction);
