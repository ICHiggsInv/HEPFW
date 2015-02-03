#include "AnalysisTools/EventFilters/interface/METJetsMinDPhiFilter.h"

// HEPFW includes
#include "Algorithm/Geometric/interface/DeltaPhi.h"

// ICHiggsTauTau
#include "DataFormats/ICHiggsTauTau/interface/Met.h"
#include "DataFormats/ICHiggsTauTau/interface/PFJet.h"

// C++ STD includes
#include <iostream>

using namespace std;

hepfw::METJetsMinDPhiFilter::METJetsMinDPhiFilter(){
  
  this->init(); // Setting default values;
  m_name = "";
}

hepfw::METJetsMinDPhiFilter::METJetsMinDPhiFilter(string name){
  
  this->init(); // Setting default values;
  m_name = name;
}

hepfw::METJetsMinDPhiFilter::METJetsMinDPhiFilter(std::string name,hepfw::ParameterSet &pset){
  
  this->init(); // Setting default values;
  m_name = name;
  
  if(pset.isParameterDefined("verbose"))      {m_verbose = pset.getParameter<bool>("verbose");}
  if(pset.isParameterDefined("metCollection")){this->setMetCollection(pset.getParameter<string>("metCollection"));}
  if(pset.isParameterDefined("jetCollection")){this->setJetCollection(pset.getParameter<string>("jetCollection"));}
  if(pset.isParameterDefined("minJetPt"))     {this->setMinJetPt     (pset.getParameter<double>("minJetPt"));}

  if(pset.isParameterDefined("minDPhi"))      {this->setMinDPhi        (pset.getParameter<double>("minDPhi"));}
  if(pset.isParameterDefined("op(minDPhi)"))  {this->setOperatorMinDPhi(pset.getParameter<string>("op(minDPhi)"));}
  
  if(m_op_minDPhi=="<"){testFunc = &hepfw::METJetsMinDPhiFilter::test_DPhi_LessThan;}
  else                 {testFunc = &hepfw::METJetsMinDPhiFilter::test_DPhi_BiggerThan;}
  
  if(m_verbose){
    
    printf("==> Initialising module: hepfw::METJetsMinDPhiFilter\n");
    printf("metCollection : %s\n",  m_metLabel.c_str());
    printf("jetCollection : %s\n",  m_jetsLabel.c_str());
    printf("minJetPt      : %.1f\n",m_minJetPt);
    printf("minDPhi       : %.2f\n",m_ref_minDPhi);
    printf("op(minDPhi)   : %s\n",  m_op_minDPhi.c_str());
  }
}

void hepfw::METJetsMinDPhiFilter::init(){
  
  m_metLabel    = "";
  m_jetsLabel   = "";
  m_minJetPt    = 0;
  m_ref_minDPhi = 0;
  m_op_minDPhi  = ">";
}

hepfw::METJetsMinDPhiFilter::~METJetsMinDPhiFilter(){
  
}

bool hepfw::METJetsMinDPhiFilter::filter(hepfw::Event &event){
  
  if(m_metLabel==""){
    cout << "[hepfw::METJetsMinDPhiFilter::evaluate] ERROR: No met collection specified." << endl;
    return false;
  }

  if(m_jetsLabel==""){
    cout << "[hepfw::METJetsMinDPhiFilter::evaluate] ERROR: No jet collection specified." << endl;
    return false;
  }
  
  ic::Met           *met  = event.getByName< ic::Met >          (m_metLabel);
  vector<ic::PFJet> *jets = event.getByName< vector<ic::PFJet> >(m_jetsLabel);
  
  double metPhi  = met->phi();
  double minDPhi = 999;
  
  for(unsigned i=0; i<jets->size(); i++){
    
    ic::PFJet *jet = &(*jets)[i];
    
    if(jet->pt()<=m_minJetPt){continue;}
    
    double thisDPhi = fabs(hepfw::deltaPhi(metPhi,jet->phi()));
    
    if(thisDPhi<minDPhi){minDPhi=thisDPhi;}
  }
  
  if(minDPhi==999)           {return false;}
  if(!testFunc(this,minDPhi)){return false;}
  
  return true;
}

void hepfw::METJetsMinDPhiFilter::setJetCollection(string jetsLabel){
  m_jetsLabel = jetsLabel;
}

void hepfw::METJetsMinDPhiFilter::setMetCollection(string metLabel){
  m_metLabel = metLabel;
}

void hepfw::METJetsMinDPhiFilter::setMinJetPt(double minPt){
  m_minJetPt = minPt;
}

void hepfw::METJetsMinDPhiFilter::setOperatorMinDPhi(std::string value){
  m_op_minDPhi = value;
}

void hepfw::METJetsMinDPhiFilter::setMinDPhi(double minDPhi){
  m_ref_minDPhi = minDPhi;
}

bool hepfw::METJetsMinDPhiFilter::test_DPhi_BiggerThan(double &value){
  return value>m_ref_minDPhi;
}

bool hepfw::METJetsMinDPhiFilter::test_DPhi_LessThan(double &value){
  return value<m_ref_minDPhi;
}
