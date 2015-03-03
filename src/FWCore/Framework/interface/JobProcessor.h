#ifndef FWCore_Framework_JobProcessor
#define FWCore_Framework_JobProcessor

// HEPFW includes
#include "FWCore/Framework/interface/ConfigurationProcessor.h"
#include "FWCore/Framework/interface/EventProcessor.h"
#include "FWCore/Framework/interface/JobProcessor.h"
#include "FWCore/Framework/interface/JobSetup.h"
#include "FWCore/Modules/interface/Module.h"
#include "FWCore/Modules/interface/ModuleSequence.h"
#include "FWCore/IO/interface/File.h"

// ROOT includes
#include "TH1I.h"

// C++ STD includes
#include <map>
#include <string>

namespace hepfw{
  
  /***********************************************/
  /** \brief JobProcessor
   * 
   * JobProcessor
   ***********************************************/
  class JobProcessor {
  public:
    
    JobProcessor();
    JobProcessor(std::string configFilename);
    ~JobProcessor();
    
    void beginJob();
    void run();
    void endJob();
    
  private:
    
    void buildSequence(std::string sequenceName,hepfw::ModuleSequence *sequence);

  private:
    
    hepfw::ConfigurationProcessor *m_cfgProcessor;
    hepfw::EventProcessor         *m_eventProcessor;
    hepfw::JobSetup               *m_jobSetup;
    
    hepfw::File                   *m_outputFile;
    
    std::map<std::string,hepfw::Module*>         m_modules;
    std::map<std::string,hepfw::ModuleSequence*> m_sequences;
    
    Long64_t m_maxEvents;
    Long64_t m_reportEvery;
    
    Long64_t m_sampleNEvents;
    Long64_t m_processedEvents;
    
    TH1I *m_eventCount;
    
  };
}

#endif  
