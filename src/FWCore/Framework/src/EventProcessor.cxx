#include "FWCore/Framework/interface/EventProcessor.h"

using namespace std;

hepfw::EventProcessor::EventProcessor(){
  m_configProcessor = 0;
  m_nEvent          = 0;
//   m_event           = new hepfw::Event();
}

hepfw::EventProcessor::EventProcessor(hepfw::ConfigurationProcessor* configProcessor){

  m_configProcessor = configProcessor;
  vector<string> vInputFiles = m_configProcessor->getInputFiles();
  
  m_eventChain = new TChain("icEventProducer/EventTree");
  
  for(unsigned i=0; i<vInputFiles.size(); i++){
    m_eventChain->Add(vInputFiles[i].c_str());
  }

  m_nEvent = m_eventChain->GetEntries();

}

hepfw::EventProcessor::~EventProcessor(){

}

Long64_t     hepfw::EventProcessor::getNEvent(){
  return m_nEvent;
}

hepfw::Event* hepfw::EventProcessor::getEvent(Long64_t eventNumber){

  hepfw::Event* ev = new hepfw::Event();
  
  ev->setTreeEventNumber(m_eventChain->LoadTree(eventNumber));
  ev->setTree           (m_eventChain->GetTree());

  return ev;
    
}