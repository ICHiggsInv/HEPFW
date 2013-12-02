#ifndef LATEX_CORE_ICLATENVIRONMENT
#define LATEX_CORE_ICLATENVIRONMENT

#include "Latex/Core/interface/ICLatexObject.h"

// C++ Included
#include <string>
#include <vector>

class ICLatexEnvironment : public ICLatexObject{
public:
  
  ICLatexEnvironment();
  ~ICLatexEnvironment();
    
  std::string toString();

  // Public variables
  std::vector<ICLatexObject*> innerObjects;
  

protected:

  // Protected methods
  std::string toStringEnvBegin();
  virtual std::string toStringEnvInner();  
  std::string toStringEnvEnd();
  
  // Protected variables
  std::string m_name;
  
private:
  
  // Private variables
  std::string m_optionsPosition;
  
};

#endif