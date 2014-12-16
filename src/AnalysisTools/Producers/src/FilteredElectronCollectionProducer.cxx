#include "AnalysisTools/Producers/interface/FilteredElectronCollectionProducer.h"

// HEPFW includes
#include "External/Utilities/interface/ElectronEffectiveArea.h"

// ICHiggsTauTau
#include "DataFormats/ICHiggsTauTau/interface/EventInfo.h"
#include "DataFormats/ICHiggsTauTau/interface/Electron.h"

using namespace std;

hepfw::FilteredElectronCollectionProducer::FilteredElectronCollectionProducer(){

  this->init(); // Setting default values;
  m_name        = "";
  m_inputLabel  = "";
  m_outputLabel = "";
}

hepfw::FilteredElectronCollectionProducer::FilteredElectronCollectionProducer(string name){

  this->init(); // Setting default values
  m_name        = name;
  m_inputLabel  = "";
  m_outputLabel = "";
}

hepfw::FilteredElectronCollectionProducer::FilteredElectronCollectionProducer(std::string name,hepfw::ParameterSet &pset){

  this->init(); // Setting default values
  m_name = name;
  
  m_inputLabel  = pset.getParameter<string>("inputLabel");
  m_outputLabel = pset.getParameter<string>("outputLabel");

  if(pset.isParameterDefined("verbose"))                    {m_verbose = pset.getParameter<bool>  ("verbose");}
  if(pset.isParameterDefined("minPt"))                      {this->setMinPt                   (pset.getParameter<double>("minPt"));}
  if(pset.isParameterDefined("maxEta"))                     {this->setMaxEta                  (pset.getParameter<double>("maxEta"));}
  if(pset.isParameterDefined("doElectronID_CutBased_Veto")) {this->doElectronID_CutBased_Veto (pset.getParameter<bool>  ("doElectronID_CutBased_Veto"));}
  if(pset.isParameterDefined("doElectronID_CutBased_Tight")){this->doElectronID_CutBased_Tight(pset.getParameter<bool>  ("doElectronID_CutBased_Tight"));}
  
  if(m_verbose){
  
    printf("==> Initialising module: hepfw::FilteredElectronCollectionProducer\n");
    printf("InputLabel        : %s\n",m_inputLabel.c_str());
    printf("OutputLabel       : %s\n",m_outputLabel.c_str());
    if(m_doMinPt                   ) {printf("MinPt                           : %.1f\n",m_minPt);}
    if(m_doMaxEta                  ) {printf("MaxEta                          : %.2f\n",m_maxEta);}
    if(m_doMaxEffAreaCorrIso       ) {printf("MaxEffAreaCorrIso               : %f\n",m_maxEffAreaCorrIso);}
    if(m_doMaxDxy                  ) {printf("MaxDxy                          : %f\n",m_maxDxy);}
    if(m_doMaxDz                   ) {printf("MaxDz                           : %f\n",m_maxDz);}
    if(m_doElectronID_CutBased_Veto) {printf("Electron ID - Cut Based - Veto  : %s\n",m_doElectronID_CutBased_Veto  ? "true" : "false");}
    if(m_doElectronID_CutBased_Tight){printf("Electron ID - Cut Based - Tight : %s\n",m_doElectronID_CutBased_Tight ? "true" : "false");}
  }
}

hepfw::FilteredElectronCollectionProducer::FilteredElectronCollectionProducer(string name,string inputLabel,string outputLabel){

  this->init(); // Setting default values
  m_name        = name;
  m_inputLabel  = inputLabel;
  m_outputLabel = outputLabel;
}

void hepfw::FilteredElectronCollectionProducer::init(){
  
  m_verbose = false;
  
  m_doMinPt             = false;
  m_doMaxEta            = false;
  m_doMaxEffAreaCorrIso = false;
  m_doMaxDxy            = false;
  m_doMaxDz             = false;
  
  m_doElectronID_CutBased_Veto  = false;
  m_doElectronID_CutBased_Tight = false;
}

hepfw::FilteredElectronCollectionProducer::~FilteredElectronCollectionProducer(){

}

void hepfw::FilteredElectronCollectionProducer::produce(hepfw::Event &event){
  
  // Getting objects from the event
  ic::ElectronCollection *inElectrons = event.getByName<ic::ElectronCollection>(m_inputLabel);
  ic::ElectronCollection  outElectrons;

  for(unsigned i=0; i<inElectrons->size(); i++){
    
    ic::Electron* el = &(*inElectrons)[i];
    
    if(m_doMinPt)            {if(el->pt()       <=m_minPt) {continue;}}
    if(m_doMaxEta)           {if(fabs(el->eta())>=m_maxEta){continue;}}
    if(m_doMaxEffAreaCorrIso){
      
      double elIso = this->calcEffAreaCorrIso(event,el);
      if(elIso>=m_maxEffAreaCorrIso){continue;}
    }
    if(m_doMaxDxy)           {if(fabs(el->dxy_vertex())>=m_maxDxy){continue;}}
    if(m_doMaxDz)            {if(fabs(el->dz_vertex()) >=m_maxDz) {continue;}}
    
    if(m_doElectronID_CutBased_Veto){
      
        // Barrel (negative logic)
        if (fabs(el->sc_eta()) <= 1.4442){
          if(fabs(el->deta_sc_tk_at_vtx())      >= 0.007){continue;}
          if(fabs(el->dphi_sc_tk_at_vtx())      >= 0.800){continue;}
          if(el->sigma_IetaIeta()               >= 0.01) {continue;}
          if(el->hadronic_over_em()             >= 0.150){continue;}
          if(fabs(el->dxy_vertex())             >= 0.04) {continue;}
          if(fabs(el->dz_vertex())              >= 0.2)  {continue;}
          if(this->calcEffAreaCorrIso(event,el) >= 0.15) {continue;}
        }
        
        // Endcap (negative logic)
        else if(fabs(el->sc_eta()) > 1.4442 && fabs(el->sc_eta()) < 2.5){
          if(fabs(el->deta_sc_tk_at_vtx())      >= 0.010){continue;}
          if(fabs(el->dphi_sc_tk_at_vtx())      >= 0.700){continue;}
          if(el->sigma_IetaIeta()               >= 0.03) {continue;}
          if(fabs(el->dxy_vertex())             >= 0.04) {continue;}
          if(fabs(el->dz_vertex())              >= 0.2)  {continue;}
          if(this->calcEffAreaCorrIso(event,el) >= 0.15) {continue;}
        }
        
        // Uknown range!?
        else{
          continue;
        }
      }

    if(m_doElectronID_CutBased_Tight){
      
      double ooemoop = fabs((1.0/el->ecal_energy() - el->sc_e_over_p()/el->ecal_energy()));
      
      // Barrel (negative logic)
      if (fabs(el->sc_eta()) <= 1.4442){
        if(fabs(el->deta_sc_tk_at_vtx())      >= 0.004){continue;}
        if(fabs(el->dphi_sc_tk_at_vtx())      >= 0.03) {continue;}
        if(el->sigma_IetaIeta()               >= 0.01) {continue;}
        if(el->hadronic_over_em()             >= 0.12) {continue;}
        if(fabs(el->dxy_vertex())             >= 0.02) {continue;}
        if(fabs(el->dz_vertex())              >= 0.1)  {continue;}
        if(ooemoop                            >= 0.05) {continue;}
        if(this->calcEffAreaCorrIso(event,el) >= 0.10) {continue;}
        if(el->has_matched_conversion())               {continue;}
        if(el->gsf_tk_nhits()                 >  0)    {continue;}
      }
      
      // Endcap (negative logic)
      else if(fabs(el->sc_eta()) > 1.4442 && fabs(el->sc_eta()) < 2.5){
        if(fabs(el->deta_sc_tk_at_vtx()) >= 0.005){continue;}
        if(fabs(el->dphi_sc_tk_at_vtx()) >= 0.02) {continue;}
        if(el->sigma_IetaIeta()          >= 0.03) {continue;}
        if(el->hadronic_over_em()        >= 0.10) {continue;}
        if(fabs(el->dxy_vertex())        >= 0.02) {continue;}
        if(fabs(el->dz_vertex())         >= 0.1)  {continue;}
        if(ooemoop                       >= 0.05) {continue;}
        if(el->pt()>20) {
          if(this->calcEffAreaCorrIso(event,el) >= 0.10) {continue;}
        }else{
          if(this->calcEffAreaCorrIso(event,el) >= 0.07) {continue;}
        }
        if(el->has_matched_conversion()){continue;}
        if(el->gsf_tk_nhits() > 0)      {continue;}
      }
    } 
    outElectrons.push_back(*el);
  }
  
  event.addProduct<ic::ElectronCollection>(m_outputLabel,outElectrons);
}

double hepfw::FilteredElectronCollectionProducer::calcEffAreaCorrIso(hepfw::Event &event,ic::Electron *el){
  
  ic::EventInfo *inEventInfo = event.getByName<ic::EventInfo>("eventInfo");
  
  // Getting lepton rho from event information
  double leptonRho = inEventInfo->lepton_rho();
  
  // Getting effective area from external class
  double leptonEffArea = ElectronEffectiveArea::GetElectronEffectiveArea(ElectronEffectiveArea::kEleGammaAndNeutralHadronIso03,el->sc_eta(),ElectronEffectiveArea::kEleEAData2012);
  double leptonIso     = el->dr03_pfiso_charged() + max(el->dr03_pfiso_gamma() + el->dr03_pfiso_neutral()-leptonRho*leptonEffArea, 0.);
  leptonIso = leptonIso / el->pt();
  
  return leptonIso;
}

void hepfw::FilteredElectronCollectionProducer::setMinPt(double value){
  m_doMinPt = true;
  m_minPt   = value;
}

void hepfw::FilteredElectronCollectionProducer::setMaxEta(double value){
  m_doMaxEta = true;
  m_maxEta   = value;
}

void hepfw::FilteredElectronCollectionProducer::setMaxEffAreaCorrIso(double value){
  m_doMaxEffAreaCorrIso = true;
  m_maxEffAreaCorrIso   = value;
}

void hepfw::FilteredElectronCollectionProducer::setMaxDxy(double value){
  m_doMaxDxy = true;
  m_maxDxy   = value;
}

void hepfw::FilteredElectronCollectionProducer::setMaxDz(double value){
  m_doMaxDz = true;
  m_maxDz   = value;
}

void hepfw::FilteredElectronCollectionProducer::doElectronID_CutBased_Veto(bool doIt){
  m_doElectronID_CutBased_Veto = doIt;
}

void hepfw::FilteredElectronCollectionProducer::doElectronID_CutBased_Tight(bool doIt){
  m_doElectronID_CutBased_Tight = doIt;
}
