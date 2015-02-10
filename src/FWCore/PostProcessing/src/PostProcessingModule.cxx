#include "FWCore/PostProcessing/interface/PostProcessingPostProcessingModule.h"

using namespace std;

hepfw::PostProcessingModule::PostProcessingModule(){
  m_name="";
  m_type=hepfw::PostProcessingModule::PostProcessingModuleType::Generic;
}

hepfw::PostProcessingModule::PostProcessingModule(std::string name){
  m_name = name;
}

hepfw::PostProcessingModule::PostProcessingModule(std::string name,hepfw::ParameterSet pset){
  m_name = name;
}

hepfw::PostProcessingModule::~PostProcessingModule(){
  
}

string hepfw::PostProcessingModule::getName(){
  return m_name;
}
