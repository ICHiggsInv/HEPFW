#include "VBFHiggsToInvisible/Analysis/interface/ZDecayFilter.h"

#include "DataFormats/ICHiggsTauTau/interface/GenParticle.h"

using namespace std;

hepfw::ZDecayFilter::ZDecayFilter(){
  m_name="";
  m_type=hepfw::ZDecayFilter::ModuleType::Filter;
}

hepfw::ZDecayFilter::ZDecayFilter(std::string name,hepfw::ParameterSet &pset,hepfw::Dataset &dataset){
  m_name      = name;
  
  string datasetName = dataset.getName();
  
  doFilter = false;
  if(datasetName.find("JetsToLL")         != datasetName.npos && 
     datasetName.find("PtZ-100-madgraph") == datasetName.npos && 
     datasetName.find("DYJJ01")           == datasetName.npos){doFilter=true;}
    
  
  flavour_ = 13;
  minMll_  = 0;
  maxMll_  = 100;

  doptinstead_ = true;

}

hepfw::ZDecayFilter::~ZDecayFilter(){
  
}


bool hepfw::ZDecayFilter::filter(hepfw::Event &event){
  
  if(doFilter){
    
    vector<ic::GenParticle> *parts = event.getByName< vector<ic::GenParticle> >("genParticles");
    
    ic::GenParticle* lepplus  = 0;
    ic::GenParticle* lepminus = 0;
    
    for (unsigned i = 0; i < parts->size(); i++) {
      
      ic::GenParticle *myGenParticle = &(*parts)[i];
      if (myGenParticle->status() != 3) continue;
      
      int id = myGenParticle->pdgid();
      
      ////if e or mu found and e or mu channel asked, just pass
      if (id == static_cast<int>(flavour_)) {
        //std::cout << " -- Found status 3 id " << id << ". Keeping event." << std::endl;
        
        lepminus = myGenParticle;
      }
      if (id == static_cast<int>(-flavour_)) {
        //std::cout << " -- Found status 3 id " << id << ". Keeping event." << std::endl;
        
        lepplus = myGenParticle;
      }
      
    }//loop on genparticles
    
    if (lepplus && lepminus) {
      double mass = (lepplus->vector()+lepminus->vector()).M();
      double pt = (lepplus->vector()+lepminus->vector()).pt();
      //std::cout << " -- Found two leptons with mass = " << mass << std::endl;
      //std::string modname=this->ModuleName();
      //Diagnostic plots if you want them
      //TFileDirectory const& dir = fs_->mkdir(("Zmass_"+modname).c_str());
      //zmass = dir.make<TH1F>("zmass","zmass",1000,0.,1000.);
      
      if(!doptinstead_){
        if (mass > minMll_ && mass < maxMll_){
          return true;
        }
      }
      else{
        if (pt > minMll_ && pt < maxMll_){
          return true;
        }
      }
    }
    
    return false;
  }else{
    return true;
  }
}
