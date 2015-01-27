#include "AnalysisTools/Producers/interface/FilteredTauCollectionProducer.h"

// ICHiggsTauTau
#include "DataFormats/ICHiggsTauTau/interface/EventInfo.h"

using namespace std;

hepfw::FilteredTauCollectionProducer::FilteredTauCollectionProducer(){
  
  this->init(); // Setting default values;
  m_name        = "";
  m_inputLabel  = "";
  m_outputLabel = "";
}

hepfw::FilteredTauCollectionProducer::FilteredTauCollectionProducer(string name){
  
  this->init(); // Setting default values;
  m_name        = name;
}

hepfw::FilteredTauCollectionProducer::FilteredTauCollectionProducer(std::string name,hepfw::ParameterSet &pset){
  
  this->init(); // Setting default values;
  m_name = name;
  
  m_inputLabel  = pset.getParameter<string>("inputLabel");
  m_outputLabel = pset.getParameter<string>("outputLabel");
  
  if(pset.isParameterDefined("verbose"))       {m_verbose = pset.getParameter<bool>  ("verbose");}
  if(pset.isParameterDefined("minPt"))         {this->setMinPt        (pset.getParameter<double>("minPt"));}
  if(pset.isParameterDefined("maxEta"))        {this->setMaxEta       (pset.getParameter<double>("maxEta"));}
  if(pset.isParameterDefined("maxDxy"))        {this->setMaxDxy       (pset.getParameter<double>("maxDxy"));}
  if(pset.isParameterDefined("maxDz"))         {this->setMaxDz        (pset.getParameter<double>("maxDz"));}
  if(pset.isParameterDefined("descriminants")) {this->setDescriminants(pset.getParameterVector<string>("descriminants"));}
  
  if(m_verbose){
    
    printf("==> Initialising module: hepfw::FilteredTauCollectionProducer\n");
    printf("InputLabel        : %s\n",m_inputLabel.c_str());
    printf("OutputLabel       : %s\n",m_outputLabel.c_str());
    
    if(m_doDiscriminants){
      printf("Descriminants     : ");
      for(unsigned i=0; i<m_discriminants.size(); i++){
        printf("%s ",m_discriminants[i].c_str());
      }
      printf("\n");
    }
    if(m_doMinPt ){printf("MinPt           : %.1f\n",m_minPt);}
    if(m_doMaxEta){printf("MaxEta          : %.2f\n",m_maxEta);}
    if(m_doMaxDxy){printf("MaxDxy          : %f\n",  m_maxDxy);}
    if(m_doMaxDz ){printf("MaxDz           : %f\n",  m_maxDz);}
  }
  
}

void hepfw::FilteredTauCollectionProducer::init(){
  
  m_inputLabel  = "";
  m_outputLabel = "";
  
  m_doMinPt         = false;
  m_doMaxEta        = false;
  m_doMaxDxy        = false;
  m_doMaxDz         = false;
  m_doDiscriminants = false;
}

hepfw::FilteredTauCollectionProducer::~FilteredTauCollectionProducer(){
  
}

void hepfw::FilteredTauCollectionProducer::produce(hepfw::Event &event){
  
  // Getting objects from the event
  ic::TauCollection *inTaus = event.getByName<ic::TauCollection>(m_inputLabel);
  
  // Collection to add to the event
  ic::TauCollection outTaus;
  
  for(unsigned i=0; i<inTaus->size(); i++){
    
    ic::Tau* tau = &(*inTaus)[i];
    
    if(m_doMinPt)       {if(!(tau->pt()               > m_minPt)) {continue;}}
    if(m_doMaxEta)      {if(!(fabs(tau->eta())        < m_maxEta)){continue;}}
    if(m_doMaxDxy)      {if(!(fabs(tau->lead_dxy_vertex()) < m_maxDxy)){continue;}}
    if(m_doMaxDz)       {if(!(fabs(tau->lead_dz_vertex())  < m_maxDz)) {continue;}}
    if(m_doDiscriminants){
      
      cout << "testing tau discriminants:" << endl;
      
      bool passType = true;
      
      for(unsigned a=0; a<m_discriminants.size(); a++){
        
        string &tauDiscriminant = m_discriminants[a];
        
        if(!(tau->GetTauID(tauDiscriminant)>0.5)){
          cout<<"Failed Tau ID: "<<tauDiscriminant<<" value="<<tau->GetTauID(tauDiscriminant)<<endl;
          passType = false; 
          break;}
        else{cout<<"Passed Tau ID: "<<tauDiscriminant<<endl;}
      }
      if(!passType){continue;}
    }
    cout << "Storing tau! pt="<<tau->pt()<<" |eta|="<<fabs(tau->eta())<<" dz="<<fabs(tau->lead_dz_vertex())<<endl;
    outTaus.push_back(*tau);
  }
  
  event.addProduct<ic::TauCollection>(m_outputLabel,outTaus);
}

void hepfw::FilteredTauCollectionProducer::setMinPt(double value){
  m_doMinPt = true;
  m_minPt   = value;
}

void hepfw::FilteredTauCollectionProducer::setMaxEta(double value){
  m_doMaxEta = true;
  m_maxEta   = value;
}

void hepfw::FilteredTauCollectionProducer::setMaxDxy(double value){
  m_doMaxDxy = true;
  m_maxDxy   = value;
}

void hepfw::FilteredTauCollectionProducer::setMaxDz(double value){
  m_doMaxDz = true;
  m_maxDz   = value;
}

void hepfw::FilteredTauCollectionProducer::setDescriminants(vector<string> values){
  m_doDiscriminants = true;
  m_discriminants = values;
}
