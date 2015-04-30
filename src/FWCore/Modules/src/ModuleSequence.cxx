#include "FWCore/Modules/interface/ModuleSequence.h"

// HEPFW includes
#include "FWCore/Modules/interface/AnalyserModule.h"
#include "FWCore/Modules/interface/FilterModule.h"
#include "FWCore/Modules/interface/ProducerModule.h"

using namespace std;

hepfw::ModuleSequence::ModuleSequence(){
  this->init();
  m_name="";
}

hepfw::ModuleSequence::ModuleSequence(string name){
  this->init();
  m_name=name;
}

void hepfw::ModuleSequence::init(){
  m_eventYieldsDirectory = 0;
  m_eventYields_Absolute = 0;
  m_eventYields_Weighted = 0;
}

hepfw::ModuleSequence::~ModuleSequence(){
  
}

void hepfw::ModuleSequence::addModule(hepfw::Module *module){
  
  m_modules.push_back(module);
  
  // Deleting previous yields if existing
  if(m_eventYields_Absolute){
    
    // If the histogram already exists and has entries produce an error message
    if(m_eventYields_Absolute->GetEntries()>0){
      cout << "[hepfw::ModuleSequence::addAnalysisCut] ERROR: ModuleSequence with name="
           << this->getName()
           << " absolute event yield has been deleted with "
           << m_eventYields_Absolute->GetEntries()
           << " entries." << endl;
    }
    delete m_eventYields_Absolute;
  }
  if(m_eventYields_Weighted){
    // If the histogram already exists and has entries produce an error message
    if(m_eventYields_Weighted->GetEntries()>0){
      cout << "[hepfw::ModuleSequence::addAnalysisCut] ERROR: ModuleSequence with name="
           << this->getName()
           << " weighted event yield has been deleted with "
           << m_eventYields_Weighted->GetEntries()
           << " entries."<< endl;
    }
    delete m_eventYields_Weighted;
  }
  
  // Creating new histograms with the extra cut
  m_eventYields_Absolute = new TH1D("EventYield_Absolute","EventYield_Absolute",m_modules.size(),-0.5,m_modules.size()-0.5);
  m_eventYields_Weighted = new TH1D("EventYield_Weighted","EventYield_Weighted",m_modules.size(),-0.5,m_modules.size()-0.5);

  // Filling bins label
  for(unsigned i=0; i<m_modules.size(); i++){
    m_eventYields_Absolute->GetXaxis()->SetBinLabel(i+1,m_modules[i]->getName().c_str());
    m_eventYields_Weighted->GetXaxis()->SetBinLabel(i+1,m_modules[i]->getName().c_str());
  }

  // If the output directory is defined put histograms there
  if(m_eventYieldsDirectory){
    m_eventYields_Absolute->SetDirectory(m_eventYieldsDirectory);
    m_eventYields_Weighted->SetDirectory(m_eventYieldsDirectory);
  }
  
}

bool hepfw::ModuleSequence::execute(hepfw::Event &event){
  
  bool out = true;
  
  for(unsigned i=0; i<m_modules.size(); i++){
    
    hepfw::Module* thisModule = m_modules[i];
    
    // For filter modules do:
    if(thisModule->getType()==hepfw::FilterModule::ModuleType::Filter){
      
      hepfw::FilterModule *m = (hepfw::FilterModule*) thisModule;

      // If the event fails the sequence we stop, if not we fill yields.
      if(!m->filter(event)){
        out = false;
        break;
      }
    }
    // For analyser modules do:
    else if(thisModule->getType()==hepfw::FilterModule::ModuleType::Analyser){

      hepfw::AnalyserModule *m = (hepfw::AnalyserModule*) thisModule;
      m->analyse(event);
    }
    // For producer modules do:
    else if(thisModule->getType()==hepfw::FilterModule::ModuleType::Producer){
      
      hepfw::ProducerModule *m = (hepfw::ProducerModule*) thisModule;
      m->produce(event);
    }
    
    m_eventYields_Absolute->Fill(i);
    m_eventYields_Weighted->Fill(i); //TODO: Implement weights
    
  }
  return out;
}

void hepfw::ModuleSequence::setName(string name){
  m_name=name;
}

void hepfw::ModuleSequence::setEventYieldDirectory(TDirectory* dir){
  m_eventYieldsDirectory = dir;
}

string hepfw::ModuleSequence::getName(){
  return m_name;
}

std::vector<hepfw::Module*> hepfw::ModuleSequence::getSequence(){
  return m_modules;
}

void hepfw::ModuleSequence::setTitle (std::string title){
  m_title = title;
}













