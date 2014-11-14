#ifndef FWCore_Framework_ConfigurationProcessor
#define FWCore_Framework_ConfigurationProcessor

// HEPFW includes
#include "FWCore/Framework/interface/Dataset.h"

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
    std::string              getOutputFile();
    
  private:
    
    std::vector<std::string> m_inputFiles;
    std::string              m_outputFilename;
    hepfw::Dataset           m_dataset;
    
  };
}

#endif 