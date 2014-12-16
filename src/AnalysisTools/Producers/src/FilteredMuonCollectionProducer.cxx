#include "AnalysisTools/Producers/interface/FilteredMuonCollectionProducer.h"

// ICHiggsTauTau
#include "DataFormats/ICHiggsTauTau/interface/EventInfo.h"

using namespace std;

hepfw::FilteredMuonCollectionProducer::FilteredMuonCollectionProducer(){

  this->init(); // Setting default values;
  m_name        = "";
  m_inputLabel  = "";
  m_outputLabel = "";
}

hepfw::FilteredMuonCollectionProducer::FilteredMuonCollectionProducer(string name){

  this->init(); // Setting default values;
  m_name        = name;
  m_inputLabel  = "";
  m_outputLabel = "";
}

hepfw::FilteredMuonCollectionProducer::FilteredMuonCollectionProducer(std::string name,hepfw::ParameterSet &pset){

  this->init(); // Setting default values;
  m_name = name;
  
  m_inputLabel  = pset.getParameter<string>("inputLabel");
  m_outputLabel = pset.getParameter<string>("outputLabel");
  
  if(pset.isParameterDefined("verbose"))       {m_verbose = pset.getParameter<bool>  ("verbose");}
  if(pset.isParameterDefined("allowedTypes"))  {this->setAllowedTypes (pset.getParameterVector<string>("allowedTypes"));}
  if(pset.isParameterDefined("minPt"))         {this->setMinPt        (pset.getParameter<double>("minPt"));}
  if(pset.isParameterDefined("maxEta"))        {this->setMaxEta       (pset.getParameter<double>("maxEta"));}
  if(pset.isParameterDefined("maxRelCombIso")) {this->setMaxRelCombIso(pset.getParameter<double>("maxRelCombIso"));}
  if(pset.isParameterDefined("maxDxy"))        {this->setMaxDxy       (pset.getParameter<double>("maxDxy"));}
  if(pset.isParameterDefined("maxDz"))         {this->setMaxDz        (pset.getParameter<double>("maxDz"));}
  if(pset.isParameterDefined("doMuonID_Tight")){this->doMuonID_Tight  (pset.getParameter<bool>  ("doMuonID_Tight"));}
  
  if(m_verbose){
    
    printf("==> Initialising module: hepfw::FilteredMuonCollectionProducer\n");
    printf("InputLabel        : %s\n",m_inputLabel.c_str());
    printf("OutputLabel       : %s\n",m_outputLabel.c_str());
    
    if(m_doAllowedTypes){
      printf("Allowed Types     : ");
      for(unsigned i=0; i<m_allowedTypes.size(); i++){
        printf("%s ",m_allowedTypes[i].c_str());
      }
      printf("\n");
    }
    if(m_doMinPt        ){printf("MinPt           : %.1f\n",m_minPt);}
    if(m_doMaxEta       ){printf("MaxEta          : %.2f\n",m_maxEta);}
    if(m_doMaxRelCombIso){printf("maxRelCombIso   : %.2f\n",m_maxRelCombIso);}
    if(m_doMaxDxy       ){printf("MaxDxy          : %f\n",  m_maxDxy);}
    if(m_doMaxDz        ){printf("MaxDz           : %f\n",  m_maxDz);}
    if(m_doMuonID_Tight ){printf("Muon ID - Tight : %s\n",  m_doMuonID_Tight  ? "true" : "false");}
  }
  
}

hepfw::FilteredMuonCollectionProducer::FilteredMuonCollectionProducer(string name,string inputLabel,string outputLabel){
  
  this->init(); // Setting default values;
  m_name        = name;
  m_inputLabel  = inputLabel;
  m_outputLabel = outputLabel;
}

void hepfw::FilteredMuonCollectionProducer::init(){
  m_doMinPt         = false;
  m_doMaxEta        = false;
  m_doMaxRelCombIso = false;
  m_doMaxDxy        = false;
  m_doMaxDz         = false;
  m_doAllowedTypes  = false;
  m_doMuonID_Tight  = false;
}

hepfw::FilteredMuonCollectionProducer::~FilteredMuonCollectionProducer(){

}

void hepfw::FilteredMuonCollectionProducer::produce(hepfw::Event &event){
  
  // Getting objects from the event
//   ic::EventInfo      *inEventInfo = event.getByName<ic::EventInfo>("eventInfo");
  ic::MuonCollection *inMuons     = event.getByName<ic::MuonCollection>(m_inputLabel);

  // Collection to add to the event
  ic::MuonCollection  outMuons;
  
  for(unsigned i=0; i<inMuons->size(); i++){
    
    ic::Muon* mu = &(*inMuons)[i];
    
    if(m_doAllowedTypes) {
      
      bool passType = false;
      
      for(unsigned i=0; i<m_allowedTypes.size(); i++){
        
        string &muType = m_allowedTypes[i];
        
        if     (muType=="Global"     && mu->is_global())    {passType = true; break;}
        else if(muType=="Tracker"    && mu->is_tracker())   {passType = true; break;}
        else if(muType=="StandAlone" && mu->is_standalone()){passType = true; break;}
      }
      if(!passType){continue;}
    }
    if(m_doMinPt)        {if(!(mu->pt()                                  > m_minPt))        {continue;}}
    if(m_doMaxEta)       {if(!(fabs(mu->eta())                           < m_maxEta))       {continue;}}
    if(m_doMaxRelCombIso){if(!(this->relativeCombinedIsolation_DR0p4(mu) < m_maxRelCombIso)){continue;}}
    if(m_doMaxDxy)       {if(!(fabs(mu->dxy_vertex())                    < m_maxDxy))       {continue;}}
    if(m_doMaxDz)        {if(!(fabs(mu->dz_vertex())                     < m_maxDz))        {continue;}}
    if(m_doMuonID_Tight) {if(!(this->isTightMuon(mu)))                                      {continue;}}
    
    outMuons.push_back(*mu);
  }
  
  event.addProduct<ic::MuonCollection>(m_outputLabel,outMuons);
}

void hepfw::FilteredMuonCollectionProducer::setMinPt(double value){
  m_doMinPt = true;
  m_minPt   = value;
}

void hepfw::FilteredMuonCollectionProducer::setMaxEta(double value){
  m_doMaxEta = true;
  m_maxEta   = value;
}

void hepfw::FilteredMuonCollectionProducer::setMaxRelCombIso(double value){
  m_doMaxRelCombIso = true;
  m_maxRelCombIso   = value;
}

void hepfw::FilteredMuonCollectionProducer::setMaxDxy(double value){
  m_doMaxDxy = true;
  m_maxDxy   = value;
}

void hepfw::FilteredMuonCollectionProducer::setMaxDz(double value){
  m_doMaxDz = true;
  m_maxDz   = value;
}

void hepfw::FilteredMuonCollectionProducer::setAllowedTypes(vector<string> values){
  m_doAllowedTypes = true;
  m_allowedTypes = values;
}

void hepfw::FilteredMuonCollectionProducer::addAllowedType(string value){
  m_doAllowedTypes = true;
  m_allowedTypes.push_back(value);
}

void hepfw::FilteredMuonCollectionProducer::doMuonID_Tight(bool doIt){
  m_doMuonID_Tight = true;
}

bool hepfw::FilteredMuonCollectionProducer::isTightMuon(ic::Muon* mu){
  
  if(!(mu->is_global()))                       {return false;} // Is a global muon
  if(!(mu->gt_normalized_chi2()         < 10)) {return false;} // Global track fit normalised Chi2
  if(!(mu->gt_valid_muon_hits()         > 0))  {return false;} // Global track fit hits in muon chamber
  if(!(mu->matched_stations()           > 1))  {return false;} // Number os stations with muon segments
  if(!(mu->dxy_vertex()                 < 0.2)){return false;} // Dxy to vertex
  if(!(mu->dz_vertex()                  < 0.5)){return false;} // Dz to vertex
  if(!(mu->it_pixel_hits()              > 0))  {return false;} // Number of pixel hits
  if(!(mu->it_layers_with_measurement() > 5))  {return false;} // Number of tracker layers with measurement
  
  return true;
}

double hepfw::FilteredMuonCollectionProducer::relativeCombinedIsolation_DR0p4(ic::Muon* mu){

  double puNeutralFraction = 0.5;
  double muIso =  mu->dr04_pfiso_charged_all() + max(mu->dr04_pfiso_neutral() + mu->dr04_pfiso_gamma() - puNeutralFraction*mu->dr04_pfiso_pu(), 0.0);
  
  return muIso / mu->pt();
}