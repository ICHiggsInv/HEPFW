#include "FWCore/Modules/interface/Module.h"

using namespace std;

hepfw::Module::Module(){
  m_name="";
  m_type=hepfw::Module::ModuleType::Generic;
}

hepfw::Module::Module(std::string name){
  m_name = name;
  m_type = hepfw::Module::ModuleType::Generic;
}

hepfw::Module::Module(std::string name,hepfw::ParameterSet pset){
  m_name = name;
  m_type = hepfw::Module::ModuleType::Generic;
}

hepfw::Module::~Module(){
  
}

string hepfw::Module::getName(){
  return m_name;
}

hepfw::Module::ModuleType hepfw::Module::getType(){
  return m_type;
}

void hepfw::Module::beginJob(hepfw::JobSetup &job){
  
}

void hepfw::Module::endJob(){
  
}
