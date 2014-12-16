#include "AnalysisTools/EventFilters/interface/HLTPathFilter.h"

// ICHiggsTauTau
#include "DataFormats/ICHiggsTauTau/interface/EventInfo.h"
#include "DataFormats/ICHiggsTauTau/interface/TriggerPath.h"

// C++ STD includes
#include <iostream>

using namespace std;

hepfw::HLTPathFilter::HLTPathFilter(){
  
  // Setting default values;
  this->init();
  
  m_name = "";
}

hepfw::HLTPathFilter::HLTPathFilter(string name){
  
  // Setting default values;
  this->init();
  
  m_name = name;
}

hepfw::HLTPathFilter::HLTPathFilter(std::string name,hepfw::ParameterSet &pset){
  
  this->init(); // Setting default values;
  m_name = name;
  
  if(pset.isParameterDefined("verbose")){m_verbose = pset.getParameter<bool>("verbose");}
  
  // Getting paths vector from configuration file
  hepfw::ParameterSet paths = pset.getParameterSet("paths");
  
  for(unsigned i=0; i<paths.size(); i++){
    
    hepfw::ParameterSet thisPath = paths.getParameterSet(i);
    vector<string> varList = thisPath.getParameterList();
    
    //TODO: Protection for this
    string *s = &varList[0];
    
    // Getting run range
    vector<int> runRange = thisPath.getParameterVector<int>(*s);
  
    this->addPath(*s,runRange[0],runRange[1]);
    
  }
  
  if(m_verbose){
    
    printf("==> Initialising module: hepfw::HLTPathFilter\n");
    for(auto selPath=m_hltPaths.begin(); selPath!=m_hltPaths.end(); selPath++){
    
      printf("==> HLT Path: %50s first run : %7d last run : %7d\n",selPath->first.c_str(),selPath->second.first,selPath->second.second);
      
    }
  }
}

void hepfw::HLTPathFilter::init(){
  m_verbose = false;
}

hepfw::HLTPathFilter::~HLTPathFilter(){
  
}

void hepfw::HLTPathFilter::addPath(std::string hltAlgo,int firstRun,int lastRun){
  
  pair<int,int> runRange(firstRun,lastRun);
  m_hltPaths.insert(pair<string,pair<int,int> >(hltAlgo,runRange));
}

bool hepfw::HLTPathFilter::filter(hepfw::Event &event){
  
  ic::EventInfo           *inEventInfo = event.getByName< ic::EventInfo >          ("eventInfo");
  vector<ic::TriggerPath> *inPaths     = event.getByName< vector<ic::TriggerPath> >("triggerPaths");
  
  int run = inEventInfo->run();
    
  // We run over our selected paths
  for(auto selPath=m_hltPaths.begin(); selPath!=m_hltPaths.end(); selPath++){
    
    // First we check if this selected trigger applies to this run
    if(run<selPath->second.first || run>selPath->second.second){continue;}
    
    for(unsigned evPath=0; evPath<inPaths->size(); evPath++){
        
      string evPathName = (*inPaths)[evPath].name();
      if(evPathName.find(selPath->first) != evPathName.npos) return true; 
    }
  }
  
  return false;
}
