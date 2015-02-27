#ifndef PostProcessing_Data_ProcessedData
#define PostProcessing_Data_ProcessedData

// HEPFW includes
#include "FWCore/Parameters/interface/ParameterSet.h"
#include "PostProcessing/Data/interface/ProcessedDataset.h"

// C++ STD includes
#include <string>

namespace hepfw{
  
  /***********************************************/
  /** \brief ProcessedData
   * 
   * ProcessedData
   ***********************************************/
  class ProcessedData {
  public:
    
    ProcessedData();
    ProcessedData(std::string name);
    ~ProcessedData();
    
    void addDataset(hepfw::ProcessedDataset dataset);
    
    TH1* getTH1_byDatasetTag (std::string datasetTag, std::string path);
    TH1* getTH1_byDatasetName(std::string datasetName,std::string path);
    
  protected:
    
    std::string                                   m_name;
    std::map<std::string,hepfw::ProcessedDataset> m_datasetMap;
    
  };
}

#endif
