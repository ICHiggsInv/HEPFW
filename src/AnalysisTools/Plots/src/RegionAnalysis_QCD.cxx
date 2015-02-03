#include "AnalysisTools/Plots/interface/RegionAnalysis_QCD.h"

// HEPFW includes
#include "Algorithm/Geometric/interface/DeltaPhi.h"

// ICHiggsTauTau includes
#include "DataFormats/ICHiggsTauTau/interface/EventInfo.h"
#include "DataFormats/ICHiggsTauTau/interface/Met.h"
#include "DataFormats/ICHiggsTauTau/interface/PFJet.h"

// ROOT includes
#include "TMath.h"

// C++ STD includes
#include <iostream>

using namespace std;

hepfw::RegionAnalysis_QCD::RegionAnalysis_QCD(){
  
  this->init(); // Setting default values;
  m_name = "";
}

hepfw::RegionAnalysis_QCD::RegionAnalysis_QCD(string name){
  
  this->init(); // Setting default values;
  m_name = name;
}

hepfw::RegionAnalysis_QCD::RegionAnalysis_QCD(std::string name,hepfw::ParameterSet &pset){
  
  this->init(); // Setting default values;
  m_name = name;
  
  if(pset.isParameterDefined("verbose"))      {m_verbose   = pset.getParameter<bool>  ("verbose");}
  if(pset.isParameterDefined("metCollection")){m_labelMet  = pset.getParameter<string>("metCollection");}
  if(pset.isParameterDefined("jetCollection")){m_labelJets = pset.getParameter<string>("jetCollection");}
  
  if(m_verbose){
    
    printf("==> Initialising module: hepfw::RegionAnalysis_QCD\n");
    printf("labelMet  : %s\n",m_labelMet.c_str());
    printf("labelJets : %s\n",m_labelJets.c_str());
    
  }
}

void hepfw::RegionAnalysis_QCD::init(){
  
  m_verbose = false;
  
  m_labelMet  = "pfMet_subtractedMuonTight";
  m_labelJets = "cleanPFJets";

}

hepfw::RegionAnalysis_QCD::~RegionAnalysis_QCD(){
  
}

void hepfw::RegionAnalysis_QCD::beginJob(hepfw::JobSetup &job){
  
  TDirectory* thisDir = job.getDirectoryModules()->mkdir(m_name.c_str());
  
  m_hEntries = new TH1D("Entries","",6,-0.5,5.5); m_hEntries->SetDirectory(thisDir);
  m_hEntries->GetXaxis()->SetBinLabel(1,"Total");
  m_hEntries->GetXaxis()->SetBinLabel(2,"QCD Region");
  m_hEntries->GetXaxis()->SetBinLabel(3,"Norm1");
  m_hEntries->GetXaxis()->SetBinLabel(4,"Norm2");
  m_hEntries->GetXaxis()->SetBinLabel(5,"Norm3");
  m_hEntries->GetXaxis()->SetBinLabel(6,"Signal Region");
  
  // Norm1
  TDirectory* qcdDir    = thisDir->mkdir("QCD");
  TDirectory* norm1Dir  = thisDir->mkdir("Norm1");
  TDirectory* norm2Dir  = thisDir->mkdir("Norm2");
  TDirectory* norm3Dir  = thisDir->mkdir("Norm3");
  TDirectory* signalDir = thisDir->mkdir("Signal");
  
  for(int i=0; i<6; i++){
  
    TDirectory*        d;
    map<string,TH1D*>* h;
    
    if     (i==0){d=thisDir;   h=&m_hBase;}
    else if(i==1){d=qcdDir;    h=&m_hQCD;}
    else if(i==2){d=norm1Dir;  h=&m_hNorm1;}
    else if(i==3){d=norm2Dir;  h=&m_hNorm2;}
    else if(i==4){d=norm3Dir;  h=&m_hNorm3;}
    else if(i==5){d=signalDir; h=&m_hSignal;}
    
    (*h)["Jets_Multiplicity"] = new TH1D("Jet_Multiplicity","Jet_Multiplicity", 11,-0.5,       10.5); (*h)["Jets_Multiplicity"]->SetDirectory(d);
    (*h)["METJets_minDPhi"]   = new TH1D("METJets_minDPhi", "METJets_minDPhi", 100,   0,TMath::Pi()); (*h)["METJets_minDPhi"]  ->SetDirectory(d);
    (*h)["METDijet_minDPhi"]  = new TH1D("METDijet_minDPhi","METDijet_minDPhi",100,   0,TMath::Pi()); (*h)["METDijet_minDPhi"] ->SetDirectory(d);
    (*h)["MET_Sig"]           = new TH1D("MET_Sig",         "MET_Sig",         100,   0,         10); (*h)["MET_Sig"]          ->SetDirectory(d);
    
  }
  
}

void hepfw::RegionAnalysis_QCD::endJob(){
  
  
}

void hepfw::RegionAnalysis_QCD::analyse(hepfw::Event &event){
  
  m_hEntries->Fill(0);
  
  ic::Met           *met  = event.getByName<ic::Met>(m_labelMet);
  vector<ic::PFJet> *jets = event.getByName< vector<ic::PFJet> >(m_labelJets);
  
  
  double metPhi  = met->phi();
  double metSig  = met->et_sig();
  double minDPhi = 999;
  
  // Assuming sorted collection
  ic::PFJet *jet0 = &(*jets)[0];
  ic::PFJet *jet1 = &(*jets)[1];
  
  double dPhi_met_jet0 = fabs(hepfw::deltaPhi(met->phi(),jet0->phi()));
  double dPhi_met_jet1 = fabs(hepfw::deltaPhi(met->phi(),jet1->phi()));
  
  double dijetMET_minDPhi = dPhi_met_jet0<dPhi_met_jet1 ? dPhi_met_jet0 : dPhi_met_jet1;
  
  // minDPhi
  for(unsigned i=0; i<jets->size(); i++){
    
    ic::PFJet *jet = &(*jets)[i];
    
    if(jet->pt()<=30){continue;}
    
    double jetPhi = jet->phi();
    double dPhi   = fabs(hepfw::deltaPhi(metPhi,jetPhi));
    
    if(dPhi<minDPhi){minDPhi=dPhi;}
  }
  
  // Base
  m_hBase["Jets_Multiplicity"]->Fill(jets->size());
  m_hBase["METJets_minDPhi"]  ->Fill(minDPhi);
  m_hBase["METDijet_minDPhi"] ->Fill(dijetMET_minDPhi);
  m_hBase["MET_Sig"]          ->Fill(metSig);
  
  // Region: QCD Shape
  if(metSig>4.0){
    m_hEntries->Fill(1);
    m_hQCD["Jets_Multiplicity"]->Fill(jets->size());
    m_hQCD["METJets_minDPhi"] ->Fill(minDPhi);
    m_hQCD["METDijet_minDPhi"]->Fill(dijetMET_minDPhi);
    m_hQCD["MET_Sig"]         ->Fill(metSig);
  }
  
  // Region: Norm1
  if(
    dijetMET_minDPhi>1.0 &&
    dijetMET_minDPhi<2.0 &&
    metSig          >3.0 &&
    metSig          <4.0
  ){
    m_hEntries->Fill(2);
    m_hNorm1["Jets_Multiplicity"]->Fill(jets->size());
    m_hNorm1["METJets_minDPhi"] ->Fill(minDPhi);
    m_hNorm1["METDijet_minDPhi"]->Fill(dijetMET_minDPhi);
    m_hNorm1["MET_Sig"]         ->Fill(metSig);
  }
  
  // Region: Norm2
  if(
    dijetMET_minDPhi>2.0 &&
    dijetMET_minDPhi<3.0 &&
    metSig          >3.0 &&
    metSig          <4.0
  ){
    m_hEntries->Fill(3);
    m_hNorm2["Jets_Multiplicity"]->Fill(jets->size());
    m_hNorm2["METJets_minDPhi"]->Fill(minDPhi);
    m_hNorm2["METDijet_minDPhi"]->Fill(dijetMET_minDPhi);
    m_hNorm2["MET_Sig"]        ->Fill(metSig);
  }
  
  // Region: Norm3
  if(
    dijetMET_minDPhi>1.0 &&
    dijetMET_minDPhi<2.0 &&
    metSig          >4.0
  ){
    m_hEntries->Fill(4);
    m_hNorm3["Jets_Multiplicity"]->Fill(jets->size());
    m_hNorm3["METJets_minDPhi"] ->Fill(minDPhi);
    m_hNorm3["METDijet_minDPhi"]->Fill(dijetMET_minDPhi);
    m_hNorm3["MET_Sig"]         ->Fill(metSig);
  }

  // Region: Signal
  if(
    dijetMET_minDPhi>2.3 &&
    metSig          >4.0
  ){
    m_hEntries->Fill(5);
    m_hSignal["Jets_Multiplicity"]->Fill(jets->size());
    m_hSignal["METJets_minDPhi"] ->Fill(minDPhi);
    m_hSignal["METDijet_minDPhi"]->Fill(dijetMET_minDPhi);
    m_hSignal["MET_Sig"]         ->Fill(metSig);
  }
  
}