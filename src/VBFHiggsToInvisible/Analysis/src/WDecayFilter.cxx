#include "VBFHiggsToInvisible/Analysis/interface/WDecayFilter.h"

#include "DataFormats/ICHiggsTauTau/interface/GenParticle.h"

using namespace std;

hepfw::WDecayFilter::WDecayFilter(){
  m_name="";
  m_type=hepfw::WDecayFilter::ModuleType::Filter;
}

hepfw::WDecayFilter::WDecayFilter(std::string name,hepfw::ParameterSet &pset,hepfw::Dataset &dataset){
  m_name      = name;
  
  string datasetName = dataset.getName();
  
  flavour_ = pset.getParameter<unsigned>("flavour");
  
  std::cout << "Flavour: " << flavour_ << std::endl;
  countStatus3_ = 0;
  countDecay_e_ = 0;
  countDecay_mu_ = 0;
  countRest_ = 0;
  do_wgammafilter_ = true;
}

hepfw::WDecayFilter::~WDecayFilter(){
  
}

bool hepfw::WDecayFilter::filter(hepfw::Event &event){
  
  bool debug = false;
  
  vector<ic::GenParticle> *parts = event.getByName< vector<ic::GenParticle> >("genParticles");
  
  for (unsigned i = 0; i < parts->size(); ++i) {
    
    if (debug) std::cout << i << " " << (*parts)[i].status() << " " << (*parts)[i].pdgid() << std::endl;
    
    if(do_wgammafilter_&&(*parts)[i].status()==2){
      unsigned id = abs((*parts)[i].pdgid());
      if(id==22){
        std::cout<<(*parts)[i].pt()<<std::endl;
        if((*parts)[i].pt()>10) return false;
      }
    }
    
    if ((*parts)[i].status() != 3 ) continue;
    
    unsigned id = abs((*parts)[i].pdgid());
    
    
    ////if e or mu found and e or mu channel asked, just pass
    if (id == flavour_ && flavour_ != 15) {
      if (debug) std::cout << " -- Found status 3 id " << id << ". Keeping event." << std::endl;
      countStatus3_++;
      return true;;
    }
    
    //for tau, find decay products
    if (id == 15) {
      if (flavour_==15) countStatus3_++;
      
      //get the specific taus collection with daughters filled
      vector<ic::GenParticle> *taus = event.getByName< vector<ic::GenParticle> >("genParticlesTaus");
      
      unsigned counter = 0;
      bool lDecay = false;
      for (unsigned j = 0; j < taus->size(); ++j) {
        if ((*taus)[j].status() == 3) {
          counter++;
          if (debug) std::cout << " ---- Tau particle " << j << " id " << (*taus)[j].pdgid() << " status " << (*taus)[j].status()  << std::endl;
          continue;
        }
        unsigned idDau = abs((*taus)[j].pdgid());
        
        if (idDau==11) {
          lDecay=true;
          countDecay_e_++;
          if (debug) std::cout << " -- Found tau decaying to an electron." << std::endl;
          if (flavour_!=11) return false;
          else return true;;
        }
        if (idDau==13) {
          lDecay=true;
          countDecay_mu_++;
          if (debug) std::cout << " -- Found tau decaying to a muon." << std::endl;
          if (flavour_!=13) return false;
          else return true;
        }

        
      }//loop on tau particles
      
      if (counter != 1) {
        std::cout << " -- Found " << counter << " tau status 3 in genParticlesTaus collection !! Expect 1 ..." << std::endl;
        throw;
      }
      //if (flavour_ == 15){// && !lDecay) {
      //std::cout << " -- Found tau decaying hadronically. Keeping event." << std::endl;
      if (!lDecay) {
        countRest_++;
        if (debug) std::cout << " -- Found tau decaying hadronically." << std::endl;
        if (flavour_ == 15) return true;
        else return false;
      }
      //return 0;
      break;
      //}
    }//found a tau status 3
    
  }//loop on genparticles
  
  if (debug) std::cout << " -- Found nothing, rejecting event." << std::endl;
  
  return false;
}
