#ifndef FWCore_Modules_JobSetup
#define FWCore_Modules_JobSetup

// HEPFW includes
#include "FWCore/IO/interface/File.h"

// ROOT includes
#include "TDirectory.h"

// C++ STD includes
#include <string>

namespace hepfw{
  
  /***********************************************/
  /** \brief JobSetup
   * 
   * JobSetup
   ***********************************************/
  class JobSetup {
  public:
    
    JobSetup();
    ~JobSetup();
    
    void setDirectorySequences(TDirectory* dir);
    void setDirectoryModules  (TDirectory* dir);
    void setOutputFile(hepfw::File* file);
    
    TDirectory*  getDirectorySequences();
    TDirectory*  getDirectoryModules();
    hepfw::File* getOutputFile();
    
  protected:
    
    hepfw::File* m_outputFile;
    
    TDirectory* m_dirSequences;
    TDirectory* m_dirModules;
  };
}

#endif 