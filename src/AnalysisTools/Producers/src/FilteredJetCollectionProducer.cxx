#include "AnalysisTools/Producers/interface/FilteredJetCollectionProducer.h"

using namespace std;

hepfw::FilteredJetCollectionProducer::FilteredJetCollectionProducer(){

  this->init(); // Setting default values
  m_name        = "";
  m_inputLabel  = "";
  m_outputLabel = "";
}

hepfw::FilteredJetCollectionProducer::FilteredJetCollectionProducer(string name){

  this->init(); // Setting default values
  m_name        = name;
  m_inputLabel  = "";
  m_outputLabel = "";
}

hepfw::FilteredJetCollectionProducer::FilteredJetCollectionProducer(std::string name,hepfw::ParameterSet &pset){

  this->init(); // Setting default values
  m_name = name;

  m_inputLabel  = pset.getParameter<string>("inputLabel");
  m_outputLabel = pset.getParameter<string>("outputLabel");
  
  if(pset.isParameterDefined("verbose"))       {m_verbose = pset.getParameter<bool>  ("verbose");}
  if(pset.isParameterDefined("minPt"))         {this->setMinPt      (pset.getParameter<double>("minPt"));}
  if(pset.isParameterDefined("maxEta"))        {this->setMaxEta     (pset.getParameter<double>("maxEta"));}
  if(pset.isParameterDefined("doPFJetID"))     {this->doPFJetID     (pset.getParameter<double>("doPFJetID"));}
  if(pset.isParameterDefined("doLoosePUIdMVA")){this->doLoosePUIdMVA(pset.getParameter<double>("doLoosePUIdMVA"));}
  
  if(m_verbose){
    
    printf("==> Initialising module: hepfw::FilteredJetCollectionProducer\n");
    printf("InputLabel        : %s\n",m_inputLabel.c_str());
    printf("OutputLabel       : %s\n",m_outputLabel.c_str());
    if(m_doMinPt       ){printf("MinPt           : %.1f\n",m_minPt);}
    if(m_doMaxEta      ){printf("MaxEta          : %.2f\n",m_maxEta);}
    if(m_doPFJetID     ){printf("PFJet ID        : %s\n",  m_doPFJetID      ? "true" : "false");}
    if(m_doLoosePUIdMVA){printf("MVA Loose PU ID : %s\n",  m_doLoosePUIdMVA ? "true" : "false");}
  }
  
}

hepfw::FilteredJetCollectionProducer::FilteredJetCollectionProducer(string name,string inputLabel,string outputLabel){

  this->init(); // Setting default values
  m_name        = name;
  m_inputLabel  = inputLabel;
  m_outputLabel = outputLabel;
  
}

hepfw::FilteredJetCollectionProducer::~FilteredJetCollectionProducer(){
  
}

void hepfw::FilteredJetCollectionProducer::init(){
  
  m_verbose        = false;
  
  m_doMinPt        = false;
  m_doMaxEta       = false;
  m_doPFJetID      = false;
  m_doLoosePUIdMVA = false;
}


void hepfw::FilteredJetCollectionProducer::produce(hepfw::Event &event){
  
  // Getting objects from the event
  ic::PFJetCollection *evJets = event.getByName<ic::PFJetCollection>(m_inputLabel);
  ic::PFJetCollection outJets;
  
  for(unsigned i=0; i<evJets->size(); i++){
    
    ic::PFJet* jet = &(*evJets)[i];
    
    if(m_doMinPt)       {if(jet->pt()<=m_minPt)        {continue;}}
    if(m_doMaxEta)      {if(fabs(jet->eta())>=m_maxEta){continue;}}
    if(m_doPFJetID)     {if(!this->calcPFJetID(jet))   {continue;}}
    if(m_doLoosePUIdMVA){if(!jet->pu_id_mva_loose())   {continue;}}
    
    outJets.push_back(*jet);
  }
  
  event.addProduct<ic::PFJetCollection>(m_outputLabel,outJets);
}


bool hepfw::FilteredJetCollectionProducer::calcPFJetID(ic::PFJet *jet){
  
  double abs_eta        = fabs(jet->eta());
  int    nConstituents  = jet->charged_multiplicity() + jet->neutral_multiplicity() + jet->HF_had_multiplicity() + jet->HF_em_multiplicity();
  double neutralHadFrac = ( jet->neutral_had_energy() + jet->HF_had_energy() ) / jet->uncorrected_energy();
  
  if(neutralHadFrac                >= 0.99){return false;}
  if(jet->neutral_em_energy_frac() >= 0.99){return false;}
  if(nConstituents                 <= 1)   {return false;} //TODO: return to 1
  
  // Additional condition for barrel
  if (abs_eta < 2.4){
    if(jet->charged_had_energy_frac() == 0.0) {return false;}
    if(jet->charged_multiplicity()    == 0)   {return false;}
    if(jet->charged_em_energy_frac()  >= 0.99){return false;}
  }

  return true;
  
}

// bool hepfw::FilteredJetCollectionProducer::calcPUIdMVALoose(hepfw::Event &event,ic::PFJet *jet){
//   
// 
//   
//   double abs_eta = fabs(jet->eta());
//   double pt = jet->pt();
//   
//   if (pt > 20. && pt <= 30) {
//     if      (abs_eta < 2.5) {return (jet->pu_id_mva_value() > -0.80);}
//     else if (abs_eta < 2.75){return (jet->pu_id_mva_value() > -0.85);}
//     else if (abs_eta < 3.0) {return (jet->pu_id_mva_value() > -0.84);}
//     else if (abs_eta < 5.0) {return (jet->pu_id_mva_value() > -0.85);} 
//     else return true;
//   }
//   else if (pt > 30.) {
//     if      (abs_eta < 2.5) {return (jet->pu_id_mva_value() > -0.80);}
//     else if (abs_eta < 2.75){return (jet->pu_id_mva_value() > -0.74);}
//     else if (abs_eta < 3.0) {return (jet->pu_id_mva_value() > -0.68);}
//     else if (abs_eta < 5.0) {return (jet->pu_id_mva_value() > -0.77);}
//     else return true;
//   } 
//   else return true;
//   
//   
// }

void hepfw::FilteredJetCollectionProducer::setMinPt(double value){
  m_doMinPt = true;
  m_minPt   = value;
}

void hepfw::FilteredJetCollectionProducer::setMaxEta(double value){
  m_doMaxEta = true;
  m_maxEta   = value;
}

void hepfw::FilteredJetCollectionProducer::doPFJetID(bool doIt){
  m_doPFJetID = doIt;
}

void hepfw::FilteredJetCollectionProducer::doLoosePUIdMVA(bool doIt){
  m_doLoosePUIdMVA = doIt;
}