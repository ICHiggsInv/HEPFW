#include "FWCore/ErrorManagement/interface/ErrorManagement.h"

using namespace std;

hepfw::ErrorManagement::ErrorManagement(){
  
  m_jobStop      = false;
  m_jobOuputCode = 0;
  
}

hepfw::ErrorManagement::~ErrorManagement(){
  
}

void hepfw::ErrorManagement::addError(string module,hepfw::ErrorManagement::ErrorType errorType,string errorMsg){
  
  hepfw::ErrorManagement::ErrorDetails e;
  
  e.type    = errorType;
  e.module  = module;
  e.message = errorMsg;
  
  // If this error is a fatal error mark this job to be stopped
  if(errorType==hepfw::ErrorManagement::ErrorType::ErrorFatal){
    m_jobStop = true;
  }

  // If there was any error job output code should not be zero
  m_jobOuputCode=1;
  
  m_errors.push_back(e);
}

string hepfw::ErrorManagement::getErrorType(hepfw::ErrorManagement::ErrorType errorType){
  
  if     (errorType==hepfw::ErrorManagement::ErrorType::ErrorFatal){return "FATAL ERROR";}
  else if(errorType==hepfw::ErrorManagement::ErrorType::Error)     {return "ERROR";}
  else if(errorType==hepfw::ErrorManagement::ErrorType::Warning)   {return "WARNING";}
  else if(errorType==hepfw::ErrorManagement::ErrorType::Note)      {return "NOTE";}
  else                                                             {return "Unknown";}
}

bool hepfw::ErrorManagement::getJobStop(){
  return m_jobStop;
}

int hepfw::ErrorManagement::getJobEnd(){
  
  if(m_errors.size()>0){
    
    printf("\n\n");
    printf("The following errors have occurred:\n");
    for(unsigned i=0; i<m_errors.size(); i++){
      printf("[%s] %s: %s",m_errors[i].module.c_str(),getErrorType(m_errors[i].type).c_str(),m_errors[i].message.c_str());
    }
    printf("\n");
  }
  
  return m_jobOuputCode;
  
}
