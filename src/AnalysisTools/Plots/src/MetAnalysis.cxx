#include "AnalysisTools/Plots/interface/MetAnalysis.h"

// C++ STD includes
#include <iostream>

// ICHiggsTauTau
#include "DataFormats/ICHiggsTauTau/interface/EventInfo.h"
#include "DataFormats/ICHiggsTauTau/interface/Met.h"
#include "DataFormats/ICHiggsTauTau/interface/Muon.h"

using namespace std;

hepfw::MetAnalysis::MetAnalysis(){
  
  this->init(); // Setting default values;
  m_name = "";
}

hepfw::MetAnalysis::MetAnalysis(string name){
  
  this->init(); // Setting default values;
  m_name = name;
}

hepfw::MetAnalysis::MetAnalysis(std::string name,hepfw::ParameterSet &pset){
  
  this->init(); // Setting default values;
  m_name = name;
  
  if(pset.isParameterDefined("verbose"))        {m_verbose         = pset.getParameter<bool>  ("verbose");}
  if(pset.isParameterDefined("labelMet"))       {m_labelMet        = pset.getParameter<string>("labelMet");}
  if(pset.isParameterDefined("labelMetNoMuon")) {m_labelMetNoMuon  = pset.getParameter<string>("labelMetNoMuon");}
  if(pset.isParameterDefined("labelMuonsLoose")){m_labelMuonsLoose = pset.getParameter<string>("labelMuonsLoose");}
  if(pset.isParameterDefined("labelMuonsTight")){m_labelMuonsTight = pset.getParameter<string>("labelMuonsTight");}
  
  if(m_verbose){
    
    printf("==> Initialising module: hepfw::MetAnalysis\n");
    printf("labelMet       : %s\n",m_labelMet.c_str());
    printf("labelMetNoMuon : %s\n",m_labelMetNoMuon.c_str());

  }
}

void hepfw::MetAnalysis::init(){
  
  m_verbose = false;
  
  m_labelMet        = "pfMetType1";
  m_labelMetNoMuon  = "pfMet_subtractedMuonTight";
  m_labelMuonsLoose = "muons_Loose";
  m_labelMuonsTight = "muons_Tight";
}

hepfw::MetAnalysis::~MetAnalysis(){
  
}

void hepfw::MetAnalysis::beginJob(hepfw::JobSetup &job){
  
  TDirectory* thisDir = job.getDirectoryModules()->mkdir(m_name.c_str());
  
  m_met       = new TH1D("pfMetType1",     "pfMetType1",     500,0,1000); m_met      ->SetDirectory(thisDir);
  m_metNoMuon = new TH1D("pfMetType1_noMu","pfMetType1_noMu",500,0,1000); m_metNoMuon->SetDirectory(thisDir);
  
  m_met_Sig       = new TH1D("pfMetType1_sig",     "pfMetType1_sig",     100,0,10); m_met_Sig      ->SetDirectory(thisDir);
  m_metNoMuon_Sig = new TH1D("pfMetType1_noMu_sig","pfMetType1_noMu_sig",100,0,40); m_metNoMuon_Sig->SetDirectory(thisDir);
  
  m_muonsLoose_multiplicity = new TH1D("muonsLoose_multiplicity","muonsLoose_multiplicity",11,-0.5,10.5); m_muonsLoose_multiplicity->SetDirectory(thisDir);
  m_muonsTight_multiplicity = new TH1D("muonsTight_multiplicity","muonsTight_multiplicity",11,-0.5,10.5); m_muonsTight_multiplicity->SetDirectory(thisDir);
  
}

void hepfw::MetAnalysis::endJob(){
  
  
}

void hepfw::MetAnalysis::analyse(hepfw::Event &event){
  
  ic::Met            *met        = event.getByName<ic::Met>           (m_labelMet);
  ic::Met            *metNoMu    = event.getByName<ic::Met>           (m_labelMetNoMuon);
  ic::MuonCollection *muonsLoose = event.getByName<ic::MuonCollection>(m_labelMuonsLoose);
  ic::MuonCollection *muonsTight = event.getByName<ic::MuonCollection>(m_labelMuonsTight);
  
  m_met      ->Fill(met->pt());
  m_metNoMuon->Fill(metNoMu->pt());
  
  m_met_Sig      ->Fill(met->et_sig());
  m_metNoMuon_Sig->Fill(metNoMu->et_sig());
  
  m_muonsLoose_multiplicity->Fill(muonsLoose->size());
  m_muonsTight_multiplicity->Fill(muonsTight->size());
}