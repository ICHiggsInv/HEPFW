#include "AnalysisTools/EventFilters/interface/EDMFilterFilter.h"

// C++ STD includes
#include <iostream>

// ICHiggsTauTau
#include "DataFormats/ICHiggsTauTau/interface/EventInfo.h"

using namespace std;

hepfw::EDMFilterFilter::EDMFilterFilter(){
  
  this->init(); // Setting default values;
  m_name = "";
}

hepfw::EDMFilterFilter::EDMFilterFilter(string name){
  
  this->init(); // Setting default values;
  m_name = name;
}

hepfw::EDMFilterFilter::EDMFilterFilter(std::string name,hepfw::ParameterSet &pset){
  
  this->init(); // Setting default values;
  m_name = name;
  
  if(pset.isParameterDefined("verbose")){m_verbose    = pset.getParameter   <bool>       ("verbose");}
  if(pset.isParameterDefined("filters")){m_edmFilters = pset.getParameterMap<string,bool>("filters");}
  
  if(m_verbose){

    printf("==> Initialising module: hepfw::EDMFilterFilter\n");
    
    for(auto i=m_edmFilters.begin(); i!=m_edmFilters.end(); i++){
      printf("Filter : %40s veto event if: %s\n",i->first.c_str(),i->second ? "true" : "false");
    }
  }
}

void hepfw::EDMFilterFilter::init(){
  
  m_verbose     = false;
  m_filterCount = 0;
}

hepfw::EDMFilterFilter::~EDMFilterFilter(){
  
  if(m_filterCount!=0){
//     delete m_filterCount;
  }
}

void hepfw::EDMFilterFilter::beginJob(hepfw::JobSetup &job){
  
  TDirectory* thisDir = job.getDirectoryModules()->mkdir(m_name.c_str());

  m_filterCount = new TH1D("eventQualityFilterCount","Event Quality Filters Count",m_edmFilters.size(),-0.5,m_edmFilters.size()-0.5);
  m_filterCount->SetDirectory(thisDir);
  
  int index = 1;
  for(auto i=m_edmFilters.begin(); i!=m_edmFilters.end(); i++){
    m_filterCount->GetXaxis()->SetBinLabel(index,i->first.c_str());
    index++;
  }
}

void hepfw::EDMFilterFilter::endJob(){
  
  
}

void hepfw::EDMFilterFilter::addFilter(std::string filterName, bool resultTofilter){

  m_edmFilters[filterName] = resultTofilter;
}

bool hepfw::EDMFilterFilter::filter(hepfw::Event &event){
  
  ic::EventInfo *inEventInfo = event.getByName<ic::EventInfo>("eventInfo");
  
  bool out = true;
  
  for(auto i=m_edmFilters.begin(); i!=m_edmFilters.end(); i++){
    
    if(inEventInfo->filter_result(i->first)==i->second){
      m_filterCount->Fill(i->first.c_str(),1);
      out = false;
    }
  }
  
  return out;
  
}

