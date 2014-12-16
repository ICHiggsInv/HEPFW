#include "FWCore/Modules/interface/AnalyserModule.h"

using namespace std;

hepfw::AnalyserModule::AnalyserModule(){
  m_name="";
  m_type=hepfw::AnalyserModule::ModuleType::Analyser;
}

hepfw::AnalyserModule::~AnalyserModule(){
  
}

void hepfw::AnalyserModule::analyse(hepfw::Event &event){
  
}
