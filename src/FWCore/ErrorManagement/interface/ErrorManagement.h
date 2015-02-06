#ifndef FWCore_ErrorManagement_ErrorManagement
#define FWCore_ErrorManagement_ErrorManagement

// HEPFW includes
#include "FWCore/Framework/interface/Dataset.h"
#include "FWCore/Parameters/interface/ParameterSet.h"
#include "Parameters/JSONParser/interface/json.h"

// ROOT includes
#include "Rtypes.h"

// C++ STD includes
#include <string>
#include <vector>
#include <utility>

namespace hepfw{
  
  /***********************************************/
  /** \brief ErrorManagement
   * 
   * ErrorManagement
   ***********************************************/
  class ErrorManagement {
  public:
    
    enum ErrorType{
      ErrorFatal,
      Error,
      Warning,
      Note
    };
    
    struct ErrorDetails{
      std::string                       module;
      hepfw::ErrorManagement::ErrorType type;
      std::string                       message;
    };
    
    ErrorManagement();
    ~ErrorManagement();
    
    void        addError(std::string module,hepfw::ErrorManagement::ErrorType errorType,std::string errorMsg);
    std::string getErrorType(hepfw::ErrorManagement::ErrorType errorType);
    
    bool        getJobStop();
    int         getJobEnd();
    
  private:
    
    // Error management
    bool                                              m_jobStop;
    int                                               m_jobOuputCode;
    std::vector<hepfw::ErrorManagement::ErrorDetails> m_errors;
    
  };
}

#endif  
