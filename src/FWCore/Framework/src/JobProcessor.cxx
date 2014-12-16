#include "FWCore/Framework/interface/JobProcessor.h"

// Automatically produced before running
#include "FWCore/Framework/interface/ModulesScan.h"

#include "FWCore/Parameters/interface/ParameterSet.h"

// ROOT includes
#include "TDirectory.h"

using namespace std;

hepfw::JobProcessor::JobProcessor(){

  // Pointer initialisation
  m_cfgProcessor   = 0;
  m_eventProcessor = 0;
  m_jobSetup       = 0;
  
  // Variable initialisation
  m_maxEvents = 0;
  
  // Histogram initialisation
  m_eventCount = 0;
}

hepfw::JobProcessor::JobProcessor(string configFilename){
  
  m_cfgProcessor   = new hepfw::ConfigurationProcessor(configFilename);
  m_eventProcessor = new hepfw::EventProcessor(m_cfgProcessor);
  m_jobSetup       = new hepfw::JobSetup();
  
  m_processedEvents     = 0;
  m_maxEvents           = m_cfgProcessor->getMaxEvents();
  string outputFilename = m_cfgProcessor->getOutputFile();
  
  m_sampleNEvents = m_eventProcessor->getNEvent();
  
  if(m_maxEvents>m_sampleNEvents){
    m_maxEvents = m_sampleNEvents;
    cout << "[vbfinvRun:] WARNING: Requested to run over " << m_maxEvents << " only "<< m_sampleNEvents << " available!" << endl;
  }else if(m_maxEvents==-1){
    m_maxEvents = m_sampleNEvents;
  }
  
  m_outputFile = new hepfw::File(outputFilename.c_str(),"RECREATE");
  //m_outputFile = new hepfw::File("test.root","RECREATE");
  m_jobSetup->setOutputFile(m_outputFile);
  
  m_eventCount = new TH1I("EventCount","EventCount",1,0.5,1.5); m_eventCount->SetDirectory(m_outputFile);
  
}

hepfw::JobProcessor::~JobProcessor(){
  
  // Writing and closing output file
  m_outputFile->Write();
  m_outputFile->Close();
  
  // Deleting objects from memory if the exist
  if(m_cfgProcessor)  {delete m_cfgProcessor;}
  if(m_eventProcessor){delete m_eventProcessor;}
  if(m_jobSetup)      {delete m_jobSetup;}
  if(m_outputFile)    {delete m_outputFile;}
  //if(m_eventCount)    {delete m_eventCount;}
  
}

void hepfw::JobProcessor::beginJob(){
 
  // Making directory for modules output
  TDirectory *dirModules   = m_outputFile->mkdir("Modules");
  m_jobSetup->setDirectoryModules(dirModules);
  
  // Making directory for sequences
  TDirectory *dirSequences = m_outputFile->mkdir("Sequences");
  m_jobSetup->setDirectorySequences(dirSequences);
  
  vector<string> runSequenceNames = m_cfgProcessor->getRunSequences();
  
  cout << "[hepfw::JobProcessor::beginJob] We are going to run " << runSequenceNames.size() << " sequence(s)" << endl;
  for(unsigned i=0; i<runSequenceNames.size(); i++){
    
    string *name = &runSequenceNames[i];
    
    if(m_sequences.find(*name) != m_sequences.end()){
      cout << "[hepfw::JobProcessor::beginJob] WARNING: Attempting run over same sequence more than once (only one sequence will be run)." << endl;
      continue;
    }
    cout << "[hepfw::JobProcessor::beginJob] Building sequence " << *name << endl;
    
    hepfw::ModuleSequence* thisSequence = new hepfw::ModuleSequence(*name);
    thisSequence->setEventYieldDirectory(dirSequences->mkdir(name->c_str()));
    
    m_sequences[*name] = thisSequence;
    
    this->buildSequence(*name,thisSequence);
  }

  
  // Starting all active modules
  for(auto i=m_modules.begin(); i!=m_modules.end(); i++){
    i->second->beginJob(*m_jobSetup);
  }
  
}

void hepfw::JobProcessor::run(){
  
  for (Long64_t i=0; i<m_maxEvents; i++){
    
    m_eventCount->Fill(1);
    
    hepfw::Event* ev = m_eventProcessor->getEvent(i);
    
    //process progress
    if(i!=0 && (i%10000)==0){std::cout << "- processing event " << i << "\r" << std::flush;}
    
    // TODO: Make this aware of all sequences
    for(auto iSeq=m_sequences.begin(); iSeq!=m_sequences.end(); iSeq++){
      iSeq->second->execute(*ev);
    }

    delete ev;
    m_processedEvents++;
  }
  
}

void hepfw::JobProcessor::endJob(){
  
  for(auto i=m_modules.begin(); i!=m_modules.end(); i++){
    i->second->endJob();
  }
  
  cout << endl << endl << "Total event processed = " << m_processedEvents << endl; 
  
  m_outputFile->Write();
  m_outputFile->Close();
  
}

void hepfw::JobProcessor::buildSequence(std::string sequenceName,hepfw::ModuleSequence *sequence){
  
  vector<string> moduleNames = m_cfgProcessor->getSequenceModules(sequenceName);
  
  for(unsigned i=0; i<moduleNames.size(); i++){
    
    string *name = &moduleNames[i];
    cout << "==> Module #" << i << " - " << *name << endl;

    Module* thisModule = 0;
    
    map<std::string,hepfw::Module*>::iterator it = m_modules.find(*name);
    
    if(it != m_modules.end()){
      thisModule = it->second;
    }else{
      
      string              moduleClass = m_cfgProcessor->getModuleClass     (*name);
      hepfw::ParameterSet modulePSet  = m_cfgProcessor->getModuleParameters(*name);
      
      thisModule = hepfw::hepfwGetModule(moduleClass,*name,modulePSet);
      
      // Adding this module to the list of active modules
      m_modules[*name] = thisModule;
    }
    
    sequence->addModule(thisModule);
    
  }
}
