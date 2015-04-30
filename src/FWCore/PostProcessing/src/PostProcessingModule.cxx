#include "FWCore/PostProcessing/interface/PostProcessingModule.h"

using namespace std;

hepfw::PostProcessingModule::PostProcessingModule(){
  m_name="";
}

hepfw::PostProcessingModule::PostProcessingModule(std::string name){
  m_name = name;
}

hepfw::PostProcessingModule::PostProcessingModule(std::string name,hepfw::ParameterSet pset){
  m_name = name;
}

hepfw::PostProcessingModule::~PostProcessingModule(){
  
}

void hepfw::PostProcessingModule::process(ProcessedDataManager& data){

}

string hepfw::PostProcessingModule::getName(){
  return m_name;
}
