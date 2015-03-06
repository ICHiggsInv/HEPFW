#ifndef PostProcessing_Modules_SequenceEventYields
#define PostProcessing_Modules_SequenceEventYields

// HEPFW includes
#include "FWCore/Parameters/interface/ParameterSet.h"
#include "FWCore/PostProcessing/interface/PostProcessingModule.h"
#include "PostProcessing/Data/interface/ProcessedDataManager.h"

#include "Latex/Table/interface/LatexTabular.h"

// C++ STD includes
#include <string>
#include <vector>

namespace hepfw{
  
  /***********************************************/
  /** \brief SequenceEventYields
   * 
   * SequenceEventYields
   ***********************************************/
  class SequenceEventYields : public hepfw::PostProcessingModule {
  public:
    
    SequenceEventYields();
    SequenceEventYields(std::string name);
    SequenceEventYields(std::string name,hepfw::ParameterSet pset);
    ~SequenceEventYields();
    
    void process(hepfw::ProcessedDataManager& data);
    
  private:
    
    void cmdFindAndReplace      (hepfw::LatexTabular &tabular,std::string find,std::string replace);
    void cmdDeleteRowByFirstCell(hepfw::LatexTabular &tabular,std::string strFind);
    
  private:
    
    std::string              m_processedData;
    std::string              m_histPath;
    std::string              m_outputFileName;
    std::vector<std::string> m_tableColumns;
    hepfw::ParameterSet      m_commands;
    
  };
}

#endif 

//DECLARE_HEPFW_POSTPROCESSINGMODULE(hepfw::SequenceEventYields);
