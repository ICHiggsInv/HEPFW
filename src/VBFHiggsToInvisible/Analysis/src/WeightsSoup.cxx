#include "VBFHiggsToInvisible/Analysis/interface/WeightsSoup.h"

// ICHiggsTauTau
#include "DataFormats/ICHiggsTauTau/interface/EventInfo.h"
#include "DataFormats/ICHiggsTauTau/interface/PileupInfo.h"
#include "DataFormats/ICHiggsTauTau/interface/Candidate.h"
#include "DataFormats/ICHiggsTauTau/interface/GenParticle.h"

// ICHiggsTauTau
#include "DataFormats/ICHiggsTauTau/interface/PFJet.h"
#include "DataFormats/ICHiggsTauTau/interface/Met.h"

using namespace std;

hepfw::WeightsSoup::WeightsSoup(){
  m_name = "";
  m_do_w_soup  = false;
  m_do_dy_soup = false;
}

hepfw::WeightsSoup::WeightsSoup(std::string name){
  m_name = name;
  m_do_w_soup  = false;
  m_do_dy_soup = false;
}

void hepfw::WeightsSoup::beginJob(hepfw::JobSetup &job){
  
}

hepfw::WeightsSoup::WeightsSoup(std::string name,hepfw::ParameterSet &pset,hepfw::Dataset &dataset){
  m_name = name;
  m_do_w_soup  = false;
  m_do_dy_soup = false;
  
  m_datasetName = dataset.getName();
  
  if(m_datasetName.find("JetsToLNu") != m_datasetName.npos) {
    
     m_do_w_soup  = true;
     SetWTargetFractions(0.74069073,  0.1776316,  0.0575658,  0.0170724, 0.00703947);
     SetWInputYields    (76102995.0, 23141598.0, 34044921.0, 15539503.0, 13382803.0);
  }
  
  if (m_datasetName.find("JetsToLL") != m_datasetName.npos && 
      m_datasetName.find("PtZ-100-madgraph") == m_datasetName.npos && 
      m_datasetName.find("DYJJ01") == m_datasetName.npos) {
    
    m_do_dy_soup = true;
    SetDYTargetFractions(0.723342373, 0.190169492, 0.061355932, 0.017322034, 0.007810169);
    SetDYInputYields(30459503.0, 24045248.0, 21852156.0, 11015445.0, 6402827.0);
  }


  if (m_do_w_soup) {
    std::cout << "Making W Soup:" << std::endl;
    std::cout << "nInc = " << n_inc_ << std::endl;
    w1_ = (n_inc_*f1_) / ( (n_inc_*f1_) + n1_ );
    w2_ = (n_inc_*f2_) / ( (n_inc_*f2_) + n2_ );
    w3_ = (n_inc_*f3_) / ( (n_inc_*f3_) + n3_ );
    w4_ = (n_inc_*f4_) / ( (n_inc_*f4_) + n4_ );
    std::cout << "f1 = " << f1_ << "\t" << "n1 = " << n1_ << "\t" << "w1 = " << w1_ << std::endl;
    std::cout << "f2 = " << f2_ << "\t" << "n2 = " << n2_ << "\t" << "w2 = " << w2_ << std::endl;
    std::cout << "f3 = " << f3_ << "\t" << "n3 = " << n3_ << "\t" << "w3 = " << w3_ << std::endl;
    std::cout << "f4 = " << f4_ << "\t" << "n4 = " << n4_ << "\t" << "w4 = " << w4_ << std::endl;
  }
  
  if (m_do_dy_soup) {
    std::cout << "Making DY Soup:" << std::endl;
    std::cout << "nInc = " << zn_inc_ << std::endl;
    zw1_ = (zn_inc_*zf1_) / ( (zn_inc_*zf1_) + zn1_ );
    zw2_ = (zn_inc_*zf2_) / ( (zn_inc_*zf2_) + zn2_ );
    zw3_ = (zn_inc_*zf3_) / ( (zn_inc_*zf3_) + zn3_ );
    zw4_ = (zn_inc_*zf4_) / ( (zn_inc_*zf4_) + zn4_ );
    std::cout << "f1 = " << zf1_ << "\t" << "n1 = " << zn1_ << "\t" << "w1 = " << zw1_ << std::endl;
    std::cout << "f2 = " << zf2_ << "\t" << "n2 = " << zn2_ << "\t" << "w2 = " << zw2_ << std::endl;
    std::cout << "f3 = " << zf3_ << "\t" << "n3 = " << zn3_ << "\t" << "w3 = " << zw3_ << std::endl;
    std::cout << "f4 = " << zf4_ << "\t" << "n4 = " << zn4_ << "\t" << "w4 = " << zw4_ << std::endl;
  }
  
  
}

hepfw::WeightsSoup::~WeightsSoup(){
  
}

void hepfw::WeightsSoup::produce(hepfw::Event &event){
  
  if (m_do_w_soup) {
    vector<ic::GenParticle> *parts = event.getByName< vector<ic::GenParticle> >("genParticles");
    bool count_jets = false;
    unsigned partons = 0;
    for (unsigned i = 0; i < parts->size(); ++i) {
      if ((*parts)[i].status() != 3) continue;
      unsigned id = abs((*parts)[i].pdgid());
      if (count_jets) { 
        if (id == 1 || id == 2 || id == 3 || id == 4 || id == 5 || id == 6 || id == 21) partons++;
      }
      if (id == 24) count_jets = true; 
    }
    if (partons > 4) {
      std::cerr << "Error making soup, event has " << partons << " partons!" << std::endl;
      throw;
    }
    if (partons == 1) event.addWeight("wsoup", w1_);
    if (partons == 2) event.addWeight("wsoup", w2_);
    if (partons == 3) event.addWeight("wsoup", w3_);
    if (partons == 4) event.addWeight("wsoup", w4_);
    
    //if (partons == 0) zeroParton = true;
    
  }
  
  if (m_do_dy_soup) {
    vector<ic::GenParticle> *parts = event.getByName< vector<ic::GenParticle> >("genParticles");
    bool count_jets = false;
    unsigned partons = 0;
    for (unsigned i = 0; i < parts->size(); ++i) {
      // std::cout << i << "\t" << parts[i]->status() << "\t" << parts[i]->pdgid() << "\t" << parts[i]->vector() << std::endl;
      if ((*parts)[i].status() != 3) continue;
      unsigned id = abs((*parts)[i].pdgid());
      if (count_jets) { 
        if (id == 1 || id == 2 || id == 3 || id == 4 || id == 5 || id == 6 || id == 21) partons++;
      }
      if (id == 23) count_jets = true; 
    }
    if (partons > 4) {
      std::cerr << "Error making soup, event has " << partons << " partons!" << std::endl;
      throw;
    }
    if (partons == 1) event.addWeight("dysoup",zw1_);
    if (partons == 2) event.addWeight("dysoup",zw2_);
    if (partons == 3) event.addWeight("dysoup",zw3_);
    if (partons == 4) event.addWeight("dysoup",zw4_);
    //if (partons == 0) zeroParton = true;
  }
  
  
}

void hepfw::WeightsSoup::SetWTargetFractions(double f0, double f1, double f2, double f3, double f4) {
  f0_ = f0;
  f1_ = f1;
  f2_ = f2;
  f3_ = f3;
  f4_ = f4;
  
}
void hepfw::WeightsSoup::SetWInputYields(double n_inc, double n1, double n2, double n3, double n4) {
  n_inc_ = n_inc;
  n1_ = n1;
  n2_ = n2;
  n3_ = n3;
  n4_ = n4;
}

void hepfw::WeightsSoup::SetDYTargetFractions(double zf0, double zf1, double zf2, double zf3, double zf4) {
  zf0_ = zf0;
  zf1_ = zf1;
  zf2_ = zf2;
  zf3_ = zf3;
  zf4_ = zf4;
  
}
void hepfw::WeightsSoup::SetDYInputYields(double zn_inc, double zn1, double zn2, double zn3, double zn4) {
  zn_inc_ = zn_inc;
  zn1_ = zn1;
  zn2_ = zn2;
  zn3_ = zn3;
  zn4_ = zn4;
}
