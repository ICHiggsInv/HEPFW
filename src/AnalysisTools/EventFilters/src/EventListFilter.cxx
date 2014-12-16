#include "AnalysisTools/EventFilters/interface/EventListFilter.h"

// ICHiggsTauTau
#include "DataFormats/ICHiggsTauTau/interface/EventInfo.h"

// BOOST includes
#include <boost/algorithm/string.hpp>

// C++ STD includes
#include <iostream>
#include <fstream>

using namespace std;

hepfw::EventListFilter::EventListFilter(){
  
  // Setting default values;
  this->init();
  
  m_name = "";
}

hepfw::EventListFilter::EventListFilter(string name){

  // Setting default values;
  this->init();

  m_name = name;
}

hepfw::EventListFilter::EventListFilter(std::string name,hepfw::ParameterSet &pset){
  
  // Setting default values;
  this->init();
  
  m_name = name;
  
  if(pset.isParameterDefined("verbose")) {m_verbose  = pset.getParameter<bool>  ("verbose");}
  if(pset.isParameterDefined("filename")){m_filePath = pset.getParameter<string>("filename");}
  
  if(m_verbose){
    
    printf("==> Initialising module: hepfw::EDMFilterFilter\n");
    printf("Filename : %s\n",m_filePath.c_str());
    
  }
  
}

void hepfw::EventListFilter::init(){
  
  m_verbose  = false;
  m_filePath = "";
}

hepfw::EventListFilter::~EventListFilter(){
  
}

void hepfw::EventListFilter::beginJob(hepfw::JobSetup &job){
  
  string STRING;
  ifstream infile;
  infile.open(m_filePath.c_str());
  
  std::string line;
  while (getline(infile, line)){

    vector<string> strs;
    boost::split(strs,line,boost::is_any_of(":"));
    
    int      run = atoi (strs[0].c_str());
    int      ls  = atoi (strs[1].c_str());
    unsigned ev  = atoll(strs[2].c_str());
    
    auto a = m_events.find(run);
    if(a != m_events.end()){
      
      auto b = a->second.find(ls);
      if(b != a->second.end()){
        m_events[run][ls].insert(ev);
      }else{
        m_events[run][ls] = set<unsigned>();
        m_events[run][ls].insert(ev);
      }
      
    }else{
      
      m_events[run]     = map<int,std::set<unsigned> >();
      m_events[run][ls] = set<unsigned>();
      m_events[run][ls].insert(ev);
    }
    
  }
  infile.close();
  
}


void hepfw::EventListFilter::setEventFilelist(std::string filePath){
  m_filePath = filePath;
}

bool hepfw::EventListFilter::filter(hepfw::Event &event){
  
  ic::EventInfo *inEventInfo = event.getByName<ic::EventInfo>("eventInfo");
  
  int      thisRun = inEventInfo->run();
  int      thisLs  = inEventInfo->lumi_block();
  unsigned thisEv  = inEventInfo->event();
  
  // Find if this run has vetoed events
  auto a = m_events.find(thisRun);
  if(a != m_events.end()){
    
    // Find if this luminosity section had vetoed events
    auto b = a->second.find(thisLs);
    if(b != a->second.end()){
      
      // Find if this is a vetoed event
      auto c = b->second.find(thisEv);
      if(c != b->second.end()){return false;}
    }
  }
  
  return true;
  
}

