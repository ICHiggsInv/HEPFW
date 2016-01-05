#include "VBFHiggsToInvisible/Analysis/interface/FinalPlots.h"

// C++ STD includes
#include <iostream>

// HEPFW includes
#include "Algorithm/Geometric/interface/DeltaPhi.h"

// ICHiggsTauTau
#include "DataFormats/ICHiggsTauTau/interface/Met.h"
#include "DataFormats/ICHiggsTauTau/interface/PFJet.h"

// ROOT includes
#include "TMath.h"

using namespace std;

hepfw::FinalPlots::FinalPlots(){
  
  this->init(); // Setting default values;
  m_name = "";
}

hepfw::FinalPlots::FinalPlots(string name){
  
  this->init(); // Setting default values;
  m_name = name;
}

hepfw::FinalPlots::FinalPlots(std::string name,hepfw::ParameterSet &pset,hepfw::Dataset &dataset){
  
  this->init(); // Setting default values;
  m_name = name;
  
  if(pset.isParameterDefined("verbose"))        {m_verbose         = pset.getParameter<bool>  ("verbose");}
  
  if(m_verbose){
    
    printf("==> Initialising module: hepfw::FinalPlots\n");

    
  }
}

void hepfw::FinalPlots::init(){
  
  m_verbose = false;
}

hepfw::FinalPlots::~FinalPlots(){
  
}

void hepfw::FinalPlots::beginJob(hepfw::JobSetup &job){
  
  TDirectory* thisDir = job.getDirectoryModules()->mkdir(m_name.c_str());

  m_sigRegion_Dijet_DeltaEta = new TH1D("sigRegion_Dijet_DeltaEta","Dijet_DeltaEta",       18,3.6,7.2); m_sigRegion_Dijet_DeltaEta->SetDirectory(thisDir);
  m_sigRegion_Dijet_Mjj      = new TH1D("sigRegion_Dijet_Mjj",     "Dijet_Mjj",          19,1200,3100); m_sigRegion_Dijet_Mjj     ->SetDirectory(thisDir);
  m_sigRegion_metNoMuon_Sig  = new TH1D("sigRegion_metNoMuon_Sig", "metNoMuon_Sig",         16,  4,16); m_sigRegion_metNoMuon_Sig ->SetDirectory(thisDir);
  m_sigRegion_metNoMuon      = new TH1D("sigRegion_metNoMuon",     "metNoMuon",            21,90, 575); m_sigRegion_metNoMuon     ->SetDirectory(thisDir);

  m_sigZmumu_Dijet_DeltaEta = new TH1D("sigZmumu_Dijet_DeltaEta","Dijet_DeltaEta",        10,3.6,7.4);  m_sigZmumu_Dijet_DeltaEta->SetDirectory(thisDir);
  m_sigZmumu_Dijet_Mjj      = new TH1D("sigZmumu_Dijet_Mjj",     "Dijet_Mjj",            6,1200,2160);  m_sigZmumu_Dijet_Mjj     ->SetDirectory(thisDir);
  m_sigZmumu_metNoMuon_Sig  = new TH1D("sigZmumu_metNoMuon_Sig", "metNoMuon_Sig",           7,  4,11);  m_sigZmumu_metNoMuon_Sig ->SetDirectory(thisDir);
  m_sigZmumu_metNoMuon      = new TH1D("sigZmumu_metNoMuon",     "metNoMuon",             16,90, 580);  m_sigZmumu_metNoMuon     ->SetDirectory(thisDir);
  
  m_sigWel_Dijet_Mjj             = new TH1D("sigWel_Dijet_Mjj",            "Dijet_Mjj",                  19,1200,3100); m_sigWel_Dijet_Mjj              ->SetDirectory(thisDir);
  m_sigWel_metNoMuon             = new TH1D("sigWel_metNoMuon",            "metNoMuon",                    21,90, 575); m_sigWel_metNoMuon              ->SetDirectory(thisDir);
  m_sigWel_MinDeltaPhiMetAllJets = new TH1D("sigWel_MinDeltaPhiMetAllJets","MinDeltaPhiMetAllJets",22,2.3,TMath::Pi()); m_sigWel_MinDeltaPhiMetAllJets->SetDirectory(thisDir);;
  
  m_sigWmu_Dijet_Mjj             = new TH1D("sigWmu_Dijet_Mjj",            "Dijet_Mjj",                  19,1200,3100); m_sigWmu_Dijet_Mjj              ->SetDirectory(thisDir);
  m_sigWmu_metNoMuon             = new TH1D("sigWmu_metNoMuon",            "metNoMuon",                    21,90, 575); m_sigWmu_metNoMuon              ->SetDirectory(thisDir);
  m_sigWmu_MinDeltaPhiMetAllJets = new TH1D("sigWmu_MinDeltaPhiMetAllJets","MinDeltaPhiMetAllJets",22,2.3,TMath::Pi()); m_sigWmu_MinDeltaPhiMetAllJets->SetDirectory(thisDir);;
  
  m_sigWta_Dijet_Mjj             = new TH1D("sigWta_Dijet_Mjj",            "Dijet_Mjj",                   6,1200,2160); m_sigWta_Dijet_Mjj              ->SetDirectory(thisDir);
  m_sigWta_metNoMuon             = new TH1D("sigWta_metNoMuon",            "metNoMuon",                    16,90, 580); m_sigWta_metNoMuon              ->SetDirectory(thisDir);
  m_sigWta_MinDeltaPhiMetAllJets = new TH1D("sigWta_MinDeltaPhiMetAllJets","MinDeltaPhiMetAllJets" , 22,0,TMath::Pi()); m_sigWta_MinDeltaPhiMetAllJets->SetDirectory(thisDir);;

  m_sigRegion_Dijet_DeltaEta->SetDefaultSumw2(true);
  m_sigRegion_Dijet_Mjj     ->SetDefaultSumw2(true);
  m_sigRegion_metNoMuon_Sig ->SetDefaultSumw2(true);
  m_sigRegion_metNoMuon     ->SetDefaultSumw2(true);

  m_sigZmumu_Dijet_DeltaEta->SetDefaultSumw2(true);
  m_sigZmumu_Dijet_Mjj     ->SetDefaultSumw2(true);
  m_sigZmumu_metNoMuon_Sig ->SetDefaultSumw2(true);
  m_sigZmumu_metNoMuon     ->SetDefaultSumw2(true);
  
  m_sigWel_Dijet_Mjj            ->SetDefaultSumw2(true);
  m_sigWel_metNoMuon            ->SetDefaultSumw2(true);
  m_sigWel_MinDeltaPhiMetAllJets->SetDefaultSumw2(true);
  
  m_sigWmu_Dijet_Mjj            ->SetDefaultSumw2(true);
  m_sigWmu_metNoMuon            ->SetDefaultSumw2(true);
  m_sigWmu_MinDeltaPhiMetAllJets->SetDefaultSumw2(true);
  
  m_sigWta_Dijet_Mjj            ->SetDefaultSumw2(true);
  m_sigWta_metNoMuon            ->SetDefaultSumw2(true);
  m_sigWta_MinDeltaPhiMetAllJets->SetDefaultSumw2(true);
  
}

void hepfw::FinalPlots::endJob(){
  
  
}

void hepfw::FinalPlots::analyse(hepfw::Event &event){
  
  double evWeight = event.getTotalWeight();
  
  ic::Met            *metNoMu    = event.getByName<ic::Met>      ("pfMet_subtractedMuonTight");
  vector<ic::PFJet>  *jets = event.getByName< vector<ic::PFJet> >("cleanPFJets");
  
  if(jets->size()>=2){
    
    // Assuming jet collection is sorted
    ic::PFJet *j0 = &(*jets)[0];
    ic::PFJet *j1 = &(*jets)[1];
    
    double px = j0->vector().px() + j1->vector().px();
    double py = j0->vector().py() + j1->vector().py();
    double pz = j0->vector().pz() + j1->vector().pz();
    double normaP = pow(px,2) + pow(py,2) + pow(pz,2);
    
    double mjj  = sqrt(pow(j0->energy()+j1->energy(),2) - normaP);
    double dEta = fabs(j0->eta()-j1->eta());
    
    double metPhi  = metNoMu->phi();
    double minDPhi = 999;
    
    for(unsigned i=0; i<jets->size(); i++){
      
      ic::PFJet *jet = &(*jets)[i];
      
      if(jet->pt()<=30){continue;}
      
      double thisDPhi = fabs(hepfw::deltaPhi(metPhi,jet->phi()));
      
      if(thisDPhi<minDPhi){minDPhi=thisDPhi;}
    }
    
    m_sigRegion_Dijet_DeltaEta    ->Fill(dEta             ,evWeight);
    m_sigRegion_Dijet_Mjj         ->Fill(mjj              ,evWeight);
    m_sigRegion_metNoMuon_Sig     ->Fill(metNoMu->et_sig(),evWeight);
    m_sigRegion_metNoMuon         ->Fill(metNoMu->pt()    ,evWeight);
    
    m_sigZmumu_Dijet_DeltaEta     ->Fill(dEta             ,evWeight);
    m_sigZmumu_Dijet_Mjj          ->Fill(mjj              ,evWeight);
    m_sigZmumu_metNoMuon_Sig      ->Fill(metNoMu->et_sig(),evWeight);
    m_sigZmumu_metNoMuon          ->Fill(metNoMu->pt()    ,evWeight);
    
    m_sigWel_Dijet_Mjj            ->Fill(mjj          ,evWeight);
    m_sigWel_metNoMuon            ->Fill(metNoMu->pt(),evWeight);
    m_sigWel_MinDeltaPhiMetAllJets->Fill(minDPhi      ,evWeight);
    
    m_sigWmu_Dijet_Mjj            ->Fill(mjj          ,evWeight);
    m_sigWmu_metNoMuon            ->Fill(metNoMu->pt(),evWeight);
    m_sigWmu_MinDeltaPhiMetAllJets->Fill(minDPhi      ,evWeight);
    
    m_sigWta_Dijet_Mjj            ->Fill(mjj          ,evWeight);
    m_sigWta_metNoMuon            ->Fill(metNoMu->pt(),evWeight);
    m_sigWta_MinDeltaPhiMetAllJets->Fill(minDPhi      ,evWeight);

  }  
  
}