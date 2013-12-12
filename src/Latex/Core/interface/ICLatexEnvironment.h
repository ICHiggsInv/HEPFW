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

  void setCentering(bool centering=true);
  void setPosition (std::string option);
  
  // Public variables
  std::vector<ICLatexObject*> innerObjects;
  

protected:

  // Protected methods
  virtual std::string toStringEnvBegin();
  virtual std::string toStringEnvInner();  
  virtual std::string toStringEnvEnd();
  
  // Protected variables
  bool        m_centering;
  std::string m_name;
  std::string m_position;
  
};

#endif