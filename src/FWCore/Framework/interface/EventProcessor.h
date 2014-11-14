#ifndef FWCore_Framework_EventProcessor
#define FWCore_Framework_EventProcessor

// HEPFW includes
#include "FWCore/Framework/interface/ConfigurationProcessor.h"
#include "FWCore/Framework/interface/Dataset.h"
#include "FWCore/Framework/interface/Event.h"
// ROOT includes
#include "TChain.h"

// C++ STD includes
#include <string>

namespace hepfw{
  
  /***********************************************/
  /** \brief EventProcessor
   * 
   * EventProcessor
   ***********************************************/
  class EventProcessor {
  public:
    
    EventProcessor();
    EventProcessor(hepfw::ConfigurationProcessor* configProcessor);
    ~EventProcessor();
    
    Long64_t      getNEvent();
    hepfw::Event* getEvent(Long64_t eventNumber);
    
  private:
    
    
    Long64_t                m_nEvent;
    hepfw::Event           *m_event;
    ConfigurationProcessor *m_configProcessor;
    TChain                 *m_eventChain;

  };
}

#endif  
