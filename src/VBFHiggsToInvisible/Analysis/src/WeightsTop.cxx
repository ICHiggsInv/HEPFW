#include "VBFHiggsToInvisible/Analysis/interface/WeightsTop.h"

// ICHiggsTauTau
#include "DataFormats/ICHiggsTauTau/interface/EventInfo.h"
#include "DataFormats/ICHiggsTauTau/interface/PileupInfo.h"
#include "DataFormats/ICHiggsTauTau/interface/Candidate.h"
#include "DataFormats/ICHiggsTauTau/interface/GenParticle.h"

// ICHiggsTauTau
#include "DataFormats/ICHiggsTauTau/interface/PFJet.h"
#include "DataFormats/ICHiggsTauTau/interface/Met.h"

using namespace std;

hepfw::WeightsTop::WeightsTop(){
  m_name = "";
}

hepfw::WeightsTop::WeightsTop(std::string name){
  m_name = name;
}

void hepfw::WeightsTop::beginJob(hepfw::JobSetup &job){
  
}

hepfw::WeightsTop::WeightsTop(std::string name,hepfw::ParameterSet &pset,hepfw::Dataset &dataset){
  m_name = name;
  
  m_datasetName = dataset.getName();
}

hepfw::WeightsTop::~WeightsTop(){
  
}

void hepfw::WeightsTop::produce(hepfw::Event &event){
  
  double top_wt = 1.0;
  
  vector<ic::GenParticle> *parts = event.getByName< vector<ic::GenParticle> >("genParticles");
  
  for (unsigned i = 0; i < parts->size(); ++i) {
    if ((*parts)[i].status() == 3 && abs((*parts)[i].pdgid()) == 6) {
      double pt = (*parts)[i].pt();
      pt = std::min(pt, 400.);
      top_wt *= std::exp(0.156-0.00137*pt);
    }
  }
  top_wt = std::sqrt(top_wt);
  event.addWeight("weight_tquark",top_wt);
  
  //madgraph ttbar reweighting
  std::size_t foundttbar = m_datasetName.find("TTJets");
  if(foundttbar!=std::string::npos){
    int ngenLeptonsStatus3=0;
    double genWeight=1;
    for (unsigned i = 0; i < parts->size(); ++i) {
      if ((*parts)[i].status() == 3 && ((abs((*parts)[i].pdgid()) == 11||(abs((*parts)[i].pdgid()) == 13)||(abs((*parts)[i].pdgid()) == 15)))) {
        ngenLeptonsStatus3++;
      }
    }       
    if(ngenLeptonsStatus3==2) { genWeight=pow(0.1086/(1./9.),2); }
    else if(ngenLeptonsStatus3==1) { genWeight=(0.1086/(1./9.))*(0.6741/(2./3.)); }
    else { genWeight=pow(0.6741/(2./3.),2); }
    event.addWeight("madgraph_ttbarbr_weight",genWeight);
  }
  
}
