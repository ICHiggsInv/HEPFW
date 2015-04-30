#include "AnalysisTools/EventFilters/interface/METDijetMinDPhiFilter.h"

// HEPFW includes
#include "Algorithm/Geometric/interface/DeltaPhi.h"

// ICHiggsTauTau
#include "DataFormats/ICHiggsTauTau/interface/Met.h"
#include "DataFormats/ICHiggsTauTau/interface/PFJet.h"

// C++ STD includes
#include <iostream>

using namespace std;

hepfw::METDijetMinDPhiFilter::METDijetMinDPhiFilter(){
  
  this->init(); // Setting default values;
  m_name = "";
}

hepfw::METDijetMinDPhiFilter::METDijetMinDPhiFilter(string name){
  
  this->init(); // Setting default values;
  m_name = name;
}

hepfw::METDijetMinDPhiFilter::METDijetMinDPhiFilter(std::string name,hepfw::ParameterSet &pset){
  
  this->init(); // Setting default values;
  m_name = name;
  
  if(pset.isParameterDefined("verbose"))      {m_verbose = pset.getParameter<bool>("verbose");}
  if(pset.isParameterDefined("metCollection")){this->setMetCollection(pset.getParameter<string>("metCollection"));}
  if(pset.isParameterDefined("jetCollection")){this->setJetCollection(pset.getParameter<string>("jetCollection"));}
  if(pset.isParameterDefined("minDPhi"))      {this->setMinDPhi      (pset.getParameter<double>("minDPhi"));}
  
  if(m_verbose){
    
    printf("==> Initialising module: hepfw::METDijetMinDPhiFilter\n");
    printf("metCollection : %s\n",  m_metLabel.c_str());
    printf("jetCollection : %s\n",  m_jetsLabel.c_str());
    printf("minDPhi       : %.2f\n",m_minDPhi);
  }
}

void hepfw::METDijetMinDPhiFilter::init(){
  
  m_metLabel   = "";
  m_jetsLabel  = "";
  m_minDPhi    =  0;

}

hepfw::METDijetMinDPhiFilter::~METDijetMinDPhiFilter(){
  
}

bool hepfw::METDijetMinDPhiFilter::filter(hepfw::Event &event){
  
  if(m_metLabel==""){
    cout << "[hepfw::METDijetMinDPhiFilter::evaluate] ERROR: No met collection specified." << endl;
    return false;
  }

  if(m_jetsLabel==""){
    cout << "[hepfw::METDijetMinDPhiFilter::evaluate] ERROR: No jet collection specified." << endl;
    return false;
  }
  
  ic::Met           *met  = event.getByName< ic::Met >          (m_metLabel);
  vector<ic::PFJet> *jets = event.getByName< vector<ic::PFJet> >(m_jetsLabel);
  
  for(unsigned i=0; i<2; i++){
    
    ic::PFJet *jet = &(*jets)[i];
    
    if(fabs(hepfw::deltaPhi(met->phi(),jet->phi()))<=m_minDPhi){return false;}
    
  }
  
  return true;
}

void hepfw::METDijetMinDPhiFilter::setMinDPhi(double minDPhi){
  m_minDPhi = minDPhi;
}

void hepfw::METDijetMinDPhiFilter::setJetCollection(string jetsLabel){
  m_jetsLabel = jetsLabel;
}

void hepfw::METDijetMinDPhiFilter::setMetCollection(string metLabel){
  m_metLabel = metLabel;
}