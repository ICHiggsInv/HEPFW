#include "AnalysisTools/CutFlows/interface/AnalysisCutMet.h"

// C++ STD includes
#include <iostream>

using namespace std;

hepfw::AnalysisCutMet::AnalysisCutMet(){
  
  this->init(); // Setting default values;
  m_name = "";
}

hepfw::AnalysisCutMet::AnalysisCutMet(string name){

  this->init(); // Setting default values;
  m_name = name;
}

hepfw::AnalysisCutMet::AnalysisCutMet(std::string name,hepfw::ParameterSet &pset){
  
  this->init(); // Setting default values;
  m_name = name;
  
  if(pset.isParameterDefined("verbose"))           {m_verbose = pset.getParameter<bool>  ("verbose");}
  if(pset.isParameterDefined("metCollection"))     {this->setMetCollection     (pset.getParameter<string>("metCollection"));}
  if(pset.isParameterDefined("minMet"))            {this->setMinMet            (pset.getParameter<double>("minMet"));}
  if(pset.isParameterDefined("minMetSignificance")){this->setMinMetSignificance(pset.getParameter<double>("minMetSignificance"));}
  
  if(m_verbose){
    
    printf("==> Initialising module: hepfw::AnalysisCutMet\n");
    printf("MET Collection : %s\n",m_metLabel.c_str());
    printf("m_minMet       : %.1f\n",m_minMet);
    printf("m_minMetSig    : %.1f\n",m_minMetSig);
  }
}

hepfw::AnalysisCutMet::~AnalysisCutMet(){
  
}

void hepfw::AnalysisCutMet::init(){

  m_metLabel  = "";
  m_minMet    = 0.;
  m_minMetSig = 0.;

}

bool hepfw::AnalysisCutMet::filter(hepfw::Event &event){
  
  if(m_metLabel==""){
    cout << "[hepfw::AnalysisCutMet::evaluate] ERROR: No met collection specified." << endl;
    return false;
  }
  ic::Met* met = event.getByName<ic::Met>(m_metLabel);
  
  // Met eta conditions
  if(met->pt()    <=m_minMet)   {return false;}
  if(met->et_sig()<=m_minMetSig){return false;}

  return true;
}

void hepfw::AnalysisCutMet::setMetCollection(string metLabel){
  m_metLabel = metLabel;
}

void hepfw::AnalysisCutMet::setMinMet(double met){
  m_minMet = met;
}

void hepfw::AnalysisCutMet::setMinMetSignificance(double metSig){
  m_minMetSig = metSig;
}
