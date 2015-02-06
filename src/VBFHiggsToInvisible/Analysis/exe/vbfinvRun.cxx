// HEPFW includes
#include "AnalysisTools/CutFlows/interface/AnalysisCut.h"
#include "AnalysisTools/CutFlows/interface/AnalysisCutDijet.h"
#include "AnalysisTools/CutFlows/interface/AnalysisCutMet.h"
#include "AnalysisTools/CutFlows/interface/AnalysisCutFlow.h"

#include "AnalysisTools/Producers/interface/FilteredElectronCollectionProducer.h"
#include "AnalysisTools/Producers/interface/FilteredMuonCollectionProducer.h"
#include "AnalysisTools/Producers/interface/FilteredJetCollectionProducer.h"
#include "AnalysisTools/Filters/interface/CollectionSizeFilter.h"

#include "AnalysisTools/EventFilters/interface/EDMFilterFilter.h"
#include "AnalysisTools/EventFilters/interface/L1TETMFilter.h"
#include "AnalysisTools/EventFilters/interface/HLTPathFilter.h"
#include "AnalysisTools/EventFilters/interface/VertexFilter.h"
#include "AnalysisTools/EventFilters/interface/METJetsMinDPhiFilter.h"
#include "AnalysisTools/EventFilters/interface/EventListFilter.h"

#include "AnalysisTools/CollectionFilters/interface/OverlapCleaning.h"
#include "FWCore/Framework/interface/ConfigurationProcessor.h"
#include "FWCore/Framework/interface/EventProcessor.h"
#include "FWCore/Framework/interface/JobProcessor.h"
#include "FWCore/Framework/interface/JobSetup.h"
#include "FWCore/Modules/interface/Module.h"
#include "FWCore/Modules/interface/ModuleSequence.h"
#include "FWCore/IO/interface/File.h"
#include "Plots/Style/interface/Style.h"

// ICHiggsTauTau
#include "DataFormats/ICHiggsTauTau/interface/Electron.h"
#include "DataFormats/ICHiggsTauTau/interface/Muon.h"

// ROOT includes
#include "TFile.h"
#include "TH1I.h"
#include "TH1D.h"

// C++ STD includes
#include <string>
#include <vector>
#include <stdint.h>
#include <iostream>
#include <fstream>
#include <sys/time.h>
#include <ctime>

using namespace std;

//#################################################################################
//#################################################################################
//#################################################################################
int main(int argc, char *argv[]){
  
  bool incorrectCmd = false;
  char *cfgFile;
  if(argc!=2){incorrectCmd=true;}
  
  if(incorrectCmd){
    printf("Usage: %s [cfgFile]\n", argv[0]);
    return 1;
  }
  else{cfgFile = argv[1];}

  hepfw::Style myStyle;
  myStyle.setTDRStyle();
  
  hepfw::JobProcessor myJob(argv[1]);
  myJob.beginJob();
  myJob.run();
  myJob.endJob();
  
  return 0;
  
};