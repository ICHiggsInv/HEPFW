#include "AnalysisTools/CutFlows/interface/AnalysisCutDijet.h"

// C++ STD includes
#include <iostream>

using namespace std;

hepfw::AnalysisCutDijet::AnalysisCutDijet(){
  
  this->init(); // Setting default values;
  m_name = "";
}

hepfw::AnalysisCutDijet::AnalysisCutDijet(string name){
  
  this->init(); // Setting default values;
  m_name = name;
}

hepfw::AnalysisCutDijet::AnalysisCutDijet(std::string name,hepfw::ParameterSet &pset){
  
  this->init(); // Setting default values;
  m_name = name;
  
  if(pset.isParameterDefined("verbose"))      {m_verbose = pset.getParameter<bool>  ("verbose");}
  if(pset.isParameterDefined("jetCollection")){this->setJetCollection(pset.getParameter<string>("jetCollection"));}
  if(pset.isParameterDefined("dijetFwdBck"))  {this->setDijetFwdBck  (pset.getParameter<bool>  ("dijetFwdBck"));}
  if(pset.isParameterDefined("dijetMinPt")){
    vector<double> dijetPt = pset.getParameterVector<double>("dijetMinPt");
    this->setDijetMinPt(dijetPt[0],dijetPt[1]);
  }
  if(pset.isParameterDefined("dijetEta")){
    vector<double> dijetEta = pset.getParameterVector<double>("dijetEta");
    this->setDijetEta(dijetEta[0],dijetEta[1]);
  }
  if(pset.isParameterDefined("dijetMinDEta")) {this->setDijetMinDEta(pset.getParameter<double>("dijetMinDEta"));}
  if(pset.isParameterDefined("dijetMinMjj"))  {this->setDijetMinMjj (pset.getParameter<double>("dijetMinMjj"));}
  
  if(m_verbose){
    
    printf("==> Initialising module: hepfw::AnalysisCutDijet\n");
    printf("Jet Collection : %s\n",m_jetsLabel.c_str());
    printf("m_fwdBck         : %s\n",  m_fwdBck ? "true" : "false");
    printf("m_jet0_minPt     : %.1f\n",m_jet0_minPt);
    printf("m_jet1_minPt     : %.1f\n",m_jet1_minPt);
    printf("m_jet_minEta     : %.2f\n",m_jet_minEta);
    printf("m_jet_maxEta     : %.2f\n",m_jet_maxEta);
    printf("m_dijet_minDEta  : %.2f\n",m_dijet_minDEta);
    printf("m_dijet_minMjj   : %.1f\n",m_dijet_minMjj);
  }
}

hepfw::AnalysisCutDijet::~AnalysisCutDijet(){
  
}

void hepfw::AnalysisCutDijet::init(){

  m_jetsLabel     = "";
  m_fwdBck        = false;
  m_jet0_minPt    =   0.;
  m_jet1_minPt    =   0.;
  m_jet_minEta    = -10.;
  m_jet_maxEta    =  10.;
  m_dijet_minDEta =   0.;
  m_dijet_minMjj  =   0.;

}

bool hepfw::AnalysisCutDijet::filter(hepfw::Event &event){

  if(m_jetsLabel==""){
    cout << "[hepfw::AnalysisCutDijet::evaluate] ERROR: No jet collection specified." << endl;
    return false;
  }
  vector<ic::PFJet>* jets = event.getByName< vector<ic::PFJet> >(m_jetsLabel);
  
  if(jets->size()<2){return false;}

  // Assuming jet collection is sorted
  ic::PFJet *j0 = &(*jets)[0];
  ic::PFJet *j1 = &(*jets)[1];
  
  // Forward-backward conditions
  if(m_fwdBck && j0->eta()*j1->eta()>=0){return false;}

  // Jets eta conditions
  if(j0->eta()<m_jet_minEta || j0->eta()>m_jet_maxEta){return false;}
  if(j1->eta()<m_jet_minEta || j1->eta()>m_jet_maxEta){return false;}

  // Jets pT conditions
  if(j0->pt()<=m_jet0_minPt){return false;}
  if(j1->pt()<=m_jet1_minPt){return false;}

  // Dijet deta condition
  if(fabs(j0->eta()-j1->eta())<=m_dijet_minDEta){return false;}

  // Dijet mjj codition
  if(m_dijet_minMjj>0){
    double px = j0->vector().px() + j1->vector().px();
    double py = j0->vector().py() + j1->vector().py();
    double pz = j0->vector().pz() + j1->vector().pz();
    double normaP = pow(px,2) + pow(py,2) + pow(pz,2);
    if(m_dijet_minMjj>=sqrt(pow(j0->energy()+j1->energy(),2) - normaP)){return false;}
  }

  return true;
}

void hepfw::AnalysisCutDijet::setJetCollection(string jetsLabel){
  m_jetsLabel = jetsLabel;
}

void hepfw::AnalysisCutDijet::setDijetFwdBck(bool fwdBck){
  m_fwdBck = fwdBck;
}

void hepfw::AnalysisCutDijet::setDijetMinPt(double jet0_pt,double jet1_pt){
  m_jet0_minPt = jet0_pt;
  m_jet1_minPt = jet1_pt;
}

void hepfw::AnalysisCutDijet::setDijetEta(double minEta,double maxEta){
  m_jet_minEta = minEta;
  m_jet_maxEta = maxEta;
}

void hepfw::AnalysisCutDijet::setDijetMinDEta(double deta){
  m_dijet_minDEta = deta;
}

void hepfw::AnalysisCutDijet::setDijetMinMjj(double mjj){
  m_dijet_minMjj = mjj;
}
