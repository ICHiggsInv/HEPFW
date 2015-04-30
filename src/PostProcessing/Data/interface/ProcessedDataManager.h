#ifndef PostProcessing_Data_ProcessedDataManager
#define PostProcessing_Data_ProcessedDataManager

// HEPFW includes
#include "FWCore/Parameters/interface/ParameterSet.h"
#include "PostProcessing/Data/interface/ProcessedData.h"

// ROOT includes
#include "TH1.h"

// C++ STD includes
#include <string>

namespace hepfw{

  /***********************************************/
  /** \brief ProcessedDataManager
   * 
   * ProcessedDataManager
   ***********************************************/
  class ProcessedDataManager {
  public:
    
    ProcessedDataManager();
    ProcessedDataManager(hepfw::ParameterSet pset);
    ~ProcessedDataManager();
    
    void addData(std::string name,hepfw::ProcessedData data);
    
    TH1* getTH1_byDataName_byDatasetTag (std::string dataName,std::string datasetTag ,std::string path);
    TH1* getTH1_byDataName_byDatasetName(std::string dataName,std::string datasetName,std::string path);
    
  protected:
    
    std::map<std::string,hepfw::ProcessedData> m_dataMap;
    
  };
}









#endif
