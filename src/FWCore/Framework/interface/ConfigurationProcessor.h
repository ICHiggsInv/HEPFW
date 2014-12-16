#ifndef FWCore_Framework_ConfigurationProcessor
#define FWCore_Framework_ConfigurationProcessor

// HEPFW includes
#include "FWCore/Framework/interface/Dataset.h"
#include "FWCore/Parameters/interface/ParameterSet.h"
#include "Parameters/JSONParser/interface/json.h"

// ROOT includes
#include "Rtypes.h"

// C++ STD includes
#include <string>
#include <vector>

namespace hepfw{
  
  /***********************************************/
  /** \brief ConfigurationProcessor
   * 
   * ConfigurationProcessor
   ***********************************************/
  class ConfigurationProcessor {
  public:
    
    ConfigurationProcessor();
    ConfigurationProcessor(std::string configFilename);
    
    ~ConfigurationProcessor();
    
    std::vector<std::string> getInputFiles();
    Long64_t                 getMaxEvents();
    std::string              getOutputFile();
    std::vector<std::string> getRunSequences();
    std::vector<std::string> getSequenceModules(std::string sequenceName);
    
    std::string              getModuleClass     (std::string moduleName);
    hepfw::ParameterSet      getModuleParameters(std::string moduleName);
    
  private:
    
    std::string getPathSrc();
    Json::Value processFile(std::string fileName);
    void        loadAllCfg();
    
  private:
    
    std::string              m_pathSrc;
    
    std::vector<std::string> m_cfgFiles;
    std::vector<std::string> m_inputFiles;
    Long64_t                 m_maxEvents;
    std::string              m_outputFilename;
    hepfw::Dataset           m_dataset;
    Json::Value              m_content;
    
  };
}

#endif 