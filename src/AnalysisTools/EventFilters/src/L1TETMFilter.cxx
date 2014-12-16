#include "AnalysisTools/EventFilters/interface/L1TETMFilter.h"

// ICHiggsTauTau
#include "DataFormats/ICHiggsTauTau/interface/Candidate.h"

// C++ STD includes
#include <iostream>

using namespace std;

hepfw::L1TETMFilter::L1TETMFilter(){
  
  // Setting default values;
  this->init();
  
  m_name = "";
}

hepfw::L1TETMFilter::L1TETMFilter(string name){
  
  // Setting default values;
  this->init();
  
  m_name      = name;
}

hepfw::L1TETMFilter::L1TETMFilter(std::string name,hepfw::ParameterSet &pset){
  
  // Setting default values;
  this->init();
  
  m_name      = name;
  
  if(pset.isParameterDefined("verbose")) {m_verbose   = pset.getParameter<bool>  ("verbose");}
  if(pset.isParameterDefined("minL1ETM")){m_minL1TETM = pset.getParameter<double>("minL1ETM");}
  
  if(m_verbose){
    
    printf("==> Initialising module: hepfw::L1TETMFilter\n");
    printf("minL1ETM : %.1f\n",m_minL1TETM);
    
  }
  
}

void hepfw::L1TETMFilter::init(){
  m_verbose   = false;
  m_minL1TETM = 0;
}

hepfw::L1TETMFilter::~L1TETMFilter(){

}

bool hepfw::L1TETMFilter::filter(hepfw::Event &event){
  
  vector<ic::Candidate> *evL1TETM = event.getByName< vector<ic::Candidate> >("l1extraMET");
  
  if(evL1TETM->size()==0){
    cout << "[hepfw::L1TETMFilter::filter] ERROR: No L1T ETM found" << endl;
    return false;
  }
  ic::Candidate *l1tETM = &(*evL1TETM)[0];
  
  if(l1tETM->pt()>=m_minL1TETM){return true;}
  else                         {return false;}
  
}

void hepfw::L1TETMFilter::setMinL1TETM(double value){
  m_minL1TETM = value;
}