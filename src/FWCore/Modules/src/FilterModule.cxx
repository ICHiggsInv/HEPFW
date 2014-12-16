#include "FWCore/Modules/interface/FilterModule.h"

using namespace std;

hepfw::FilterModule::FilterModule(){
  m_name="";
  m_type=hepfw::FilterModule::ModuleType::Filter;
}

hepfw::FilterModule::~FilterModule(){
  
}

bool hepfw::FilterModule::filter(hepfw::Event &event){
  return true;
}
