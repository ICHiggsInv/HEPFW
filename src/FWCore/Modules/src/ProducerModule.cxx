#include "FWCore/Modules/interface/ProducerModule.h"

using namespace std;

hepfw::ProducerModule::ProducerModule(){
  m_name="";
  m_type=hepfw::ProducerModule::ModuleType::Producer;
}

hepfw::ProducerModule::~ProducerModule(){
  
}

void hepfw::ProducerModule::produce(hepfw::Event &event){
  
}
