#ifndef PostProcessing_Data_ProcessedDataset
#define PostProcessing_Data_ProcessedDataset

// HEPFW includes
#include "FWCore/IO/interface/File.h"

// ROOT includes
#include "TH1.h"

namespace hepfw{
  
  /***********************************************/
  /** \brief ProcessedDataset
   * 
   * ProcessedDataset
   ***********************************************/
  class ProcessedDataset {
  public:
    
    ProcessedDataset();
    ProcessedDataset(std::string name);
    ~ProcessedDataset();
    
    void init();
    
    void setName          (std::string value);
    void setType          (std::string value);
    void setTagCollection (std::vector<std::string>  value);
    void setFileCollection(std::vector<hepfw::File*> value);
    
    std::string               getName();
    std::string               getType();
    std::vector<std::string>  getTagCollection();
    std::vector<hepfw::File*> getFileCollection();
    
    void addTag (std::string  value);
    void addFile(hepfw::File* value);
    
    bool hasTag(std::string value);
    
    TH1* getTH1(std::string path);
    
  private:
    
    std::string               m_type;
    std::string               m_name;
    std::vector<std::string>  m_tagCollection;
    std::vector<hepfw::File*> m_fileCollection;
    
  };
}


#endif