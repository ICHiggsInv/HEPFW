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
  
  
  /*
  hepfw::ConfigurationProcessor myCfgProcessor(argv[1]);
  string outputFilename = myCfgProcessor.getOutputFile();

  hepfw::EventProcessor myEventProcessor(&myCfgProcessor);
  Long64_t nevents   = myEventProcessor.getNEvent();
  Long64_t maxEvents = myCfgProcessor.getMaxEvents();
  
  
  hepfw::JobSetup myJobSetup;
  // Checking maxEvents
  if(maxEvents>nevents){
    maxEvents = nevents;
    cout << "[vbfinvRun:] WARNING: Requested to run over " << maxEvents << " only "<< nevents << " available!" << endl;
  }else if(maxEvents==-1){
    maxEvents = nevents;
  }
  cout << "Number of entries: " << nevents << endl;
  
 
  hepfw::File fOut(outputFilename.c_str(),"RECREATE");
  myJobSetup.setOutputFile(&fOut);
  
  TH1I hEventCount("EventCount","EventCount",1,0.5,1.5); hEventCount.SetDirectory(&fOut);
  
  hepfw::VertexFilter vertexFilter("Vertex Filter");
  
  hepfw::EDMFilterFilter eventQualityFilters("Event Quality Filters");
  eventQualityFilters.addFilter("HBHENoiseFilter",                   false);
  eventQualityFilters.addFilter("EcalDeadCellTriggerPrimitiveFilter",false);
  eventQualityFilters.addFilter("eeBadScFilter",                     false);
  eventQualityFilters.addFilter("trackingFailureFilter",             false);
  eventQualityFilters.addFilter("manystripclus53X",                  false);
  eventQualityFilters.addFilter("toomanystripclus53X",               false);
  eventQualityFilters.addFilter("logErrorTooManyClusters",           false);
  eventQualityFilters.addFilter("CSCTightHaloFilter",                true);
  
  hepfw::EventListFilter ecalLaserFilter("ECAL Laser Filter");
  ecalLaserFilter.setEventFilelist("/home/hep/jca10/go/cms02/work/slc6/dev01/ICHiggsTauTau/Analysis/HiggsNuNu/data/met_laser_filters/ecalLaserFilter_MET_Run2012AandB.txt");

  hepfw::EventListFilter hcalLaserFilter("HCAL Laser Filter");
  hcalLaserFilter.setEventFilelist("/home/hep/jca10/go/cms02/work/slc6/dev01/ICHiggsTauTau/Analysis/HiggsNuNu/data/met_laser_filters/AllBadHCALLaser.txt");
  
  hepfw::L1TETMFilter l1tETMFilter("L1T ETM Filter");
  l1tETMFilter.setMinL1TETM(40);
  
  hepfw::HLTPathFilter parkedDataHLTFilter("HLT Trigger");
  parkedDataHLTFilter.addPath("HLT_DiPFJet40_PFMETnoMu65_MJJ800VBF_AllJets",190456,193621); // Run 2012 A 
  parkedDataHLTFilter.addPath("HLT_DiJet35_MJJ700_AllJets_DEta3p5_VBF",     193833,196531); // Run 2012 B 
  parkedDataHLTFilter.addPath("HLT_DiJet35_MJJ700_AllJets_DEta3p5_VBF",     198022,203742); // Run 2012 C 
  parkedDataHLTFilter.addPath("HLT_DiJet30_MJJ700_AllJets_DEta3p5_VBF",     203777,208686); // Run 2012 D 
  
  hepfw::FilteredElectronCollectionProducer producerLooseElectrons("Loose Electrons Producer");
  producerLooseElectrons.setInputLabel ("electrons");
  producerLooseElectrons.setOutputLabel("looseElectrons");
  producerLooseElectrons.doElectronID_CutBased_Veto(true);
  producerLooseElectrons.setMinPt (10);
  producerLooseElectrons.setMaxEta(2.4);
  
  hepfw::FilteredMuonCollectionProducer producerLooseMuon("Loose Muon Producer");
  producerLooseMuon.setInputLabel ("muonsPFlow");
  producerLooseMuon.setOutputLabel("looseMuons");
  producerLooseMuon.setMinPt        (10);
  producerLooseMuon.setMaxEta       (2.1);
  producerLooseMuon.setMaxRelCombIso(0.15);
  producerLooseMuon.setAllowedTypes (true,true,false); // Selection Global or Tracker muons (not just standalone)

  hepfw::FilteredJetCollectionProducer producerSelJets("Selected Jet Producer");
  producerSelJets.setInputLabel ("pfJetsPFlow");
  producerSelJets.setOutputLabel("selPFJets");
  producerSelJets.doPFJetID     (true);
  producerSelJets.doLoosePUIdMVA(true);
  
  // Cleaning jets from electrons
  hepfw::OverlapCleaning<ic::PFJet,ic::Electron> jetsLooseElectonCleaning("PFJets-Loose Electron cleaning");
  jetsLooseElectonCleaning.setLabelCollectionToClean  ("selPFJets");
  jetsLooseElectonCleaning.setLabelCollectionReference("looseElectrons");
  jetsLooseElectonCleaning.setLabelCollectionOutput   ("electronCleanPFJets");
  jetsLooseElectonCleaning.setMinDeltaR               (0.5);
  
  // Cleaning jets from muons
  hepfw::OverlapCleaning<ic::PFJet,ic::Muon> jetsLooseMuonCleaning("PFJets-Loose Muon cleaning");
  jetsLooseMuonCleaning.setLabelCollectionToClean  ("electronCleanPFJets");
  jetsLooseMuonCleaning.setLabelCollectionReference("looseMuons");
  jetsLooseMuonCleaning.setLabelCollectionOutput   ("cleanPFJets");
  jetsLooseMuonCleaning.setMinDeltaR               (0.5);
  
  hepfw::AnalysisCutDijet cut_dijet("Dijet");
  cut_dijet.setJetCollection("cleanPFJets");
  cut_dijet.setDijetFwdBck (true);
  cut_dijet.setDijetMinPt  (50,40);
  cut_dijet.setDijetEta    (-4.7,4.7);
  cut_dijet.setDijetMinDEta(3.6);
  cut_dijet.setDijetMinMjj (1000);
  
  hepfw::AnalysisCutMet cut_met("MET Cut");
  cut_met.setMetCollection("pfMetType1");
  cut_met.setMinMet(90);
  
  hepfw::AnalysisCutMet cut_metSig("MET Significance");
  cut_metSig.setMetCollection("pfMetType1");
  cut_metSig.setMinMetSignificance(3.0);
  
  hepfw::CollectionSizeFilter<ic::Electron> vetoElectrons("Electron veto");
  vetoElectrons.setInputLabel("looseElectrons");
  vetoElectrons.setMaxN(0);
  
  hepfw::CollectionSizeFilter<ic::Muon> vetoMuon("Muon veto");
  vetoMuon.setInputLabel("looseMuons");
  vetoMuon.setMaxN(0);
  
  hepfw::METJetsMinDPhiFilter cut_minJetMetDPhi("MET Jets DPhi");
  cut_minJetMetDPhi.setMetCollection("pfMetType1");
  cut_minJetMetDPhi.setJetCollection("cleanPFJets");
  cut_minJetMetDPhi.setMinJetPt(30);
  cut_minJetMetDPhi.setMinDPhi (1.0);
  
  hepfw::FilteredElectronCollectionProducer producerTightElectrons("Tight Electrons Producer");
  producerTightElectrons.setInputLabel ("electrons");
  producerTightElectrons.setOutputLabel("tightElectrons");
  producerTightElectrons.doElectronID_CutBased_Tight(true);
  producerTightElectrons.setMinPt (20);
  producerTightElectrons.setMaxEta(2.4);

  
  // Cleaning electron from muons
  hepfw::OverlapCleaning<ic::Electron,ic::Muon> electronMuonCleaning("Tight Electron-Loose Muon cleaning");
  electronMuonCleaning.setLabelCollectionToClean  ("tightElectrons");
  electronMuonCleaning.setLabelCollectionReference("looseMuons");
  electronMuonCleaning.setLabelCollectionOutput   ("cleanTightElectrons");
  electronMuonCleaning.setMinDeltaR               (0.3);
  
  hepfw::FilteredMuonCollectionProducer producerTightMuon("Tight Muon Producer");
  producerTightMuon.setInputLabel ("muonsPFlow");
  producerTightMuon.setOutputLabel("tightMuons");
  producerTightMuon.setMinPt        (20);
  producerTightMuon.setMaxEta       (2.1);
  producerTightMuon.setMaxRelCombIso(0.12);
  producerTightMuon.setMaxDxy       (0.045);
  producerTightMuon.setMaxDz        (0.2);
  producerTightMuon.setAllowedTypes (true,false,false); // Selection Global (not just tracker or standalone)
  
  //hepfw::AnalysisCutDijet test_dijet("test Dijet");
  //test_dijet.setJetCollection("cleanPFJets");
  //test_dijet.setDijetFwdBck (true);
  //test_dijet.setDijetMinPt  (30,30);
  //test_dijet.setDijetEta    (-4.7,4.7);
  //test_dijet.setDijetMinDEta(3.6);
  
  // Sequence definition
  hepfw::ModuleSequence preSelection("PreSelection");
  preSelection.setEventYieldDirectory(fOut.mkdir("PreSelection"));
  preSelection.addModule(&vertexFilter);
  preSelection.addModule(&l1tETMFilter);
  preSelection.addModule(&parkedDataHLTFilter);
  preSelection.addModule(&eventQualityFilters);
  preSelection.addModule(&ecalLaserFilter);
  preSelection.addModule(&hcalLaserFilter);
  preSelection.addModule(&producerLooseElectrons);
  preSelection.addModule(&vetoElectrons);
  preSelection.addModule(&producerLooseMuon);
  preSelection.addModule(&vetoMuon);
  preSelection.addModule(&producerSelJets);
  preSelection.addModule(&jetsLooseElectonCleaning);
  preSelection.addModule(&jetsLooseMuonCleaning);
//   preSelection.addModule(&test_dijet); // TODO: Remove later
  preSelection.addModule(&cut_met);
  preSelection.addModule(&cut_metSig);
  preSelection.addModule(&cut_dijet);
  preSelection.addModule(&cut_minJetMetDPhi);
  
  // Out for now
  //preSelection.addModule(&producerTightElectrons);
  //preSelection.addModule(&producerTightMuon);

  //===============================================================
  // We start processing
  //===============================================================

  map<std::string,hepfw::Module*> activeModules;

  vector<hepfw::Module*> thisSequenceModules = preSelection.getSequence();
  for(unsigned i=0; i<thisSequenceModules.size(); i++){
    
    hepfw::Module* iModule = thisSequenceModules[i];
    activeModules[iModule->getName()] = iModule;
  }
  
  //===============================================================
  
  for(auto i=activeModules.begin(); i!=activeModules.end(); i++){
    i->second->beginJob(myJobSetup);
  }
  
  //===============================================================
  
  int ntot=0;
  //loop over the events
  for (Long64_t i=0; i<maxEvents; i++){
    
    hEventCount.Fill(1);
    
    hepfw::Event* ev = myEventProcessor.getEvent(i);

    //process progress
    if(i!=0 && (i%10000)==0){std::cout << "- processing event " << i << "\r" << std::flush;}
    
    preSelection.execute(*ev);

    delete ev;
    ntot++;
    
  }
  
  //===============================================================

  for(auto i=activeModules.begin(); i!=activeModules.end(); i++){
    i->second->endJob();
  }
  
  //===============================================================
  
  cout << endl << endl << "Total event processed = " << ntot << endl; 
  
  fOut.Write();
  fOut.Close();
*/
  return 0;
  
};