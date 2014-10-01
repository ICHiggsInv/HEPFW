#ifndef LATEX_CORE_LATENVIRONMENT
#define LATEX_CORE_LATENVIRONMENT

#include "Latex/Core/interface/LatexObject.h"

// C++ Included
#include <string>
#include <vector>

namespace hepfw{
  
  /***********************************************/
  /** \brief 
   * 
   * 
   ***********************************************/
  class LatexEnvironment : public LatexObject{
  public:
    
    LatexEnvironment();
    ~LatexEnvironment();
    
    std::string toString();
    
    void setCentering(bool centering=true);
    void setPosition (std::string option);
    
    // Public variables
    std::vector<LatexObject*> innerObjects;
    
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
  
}

#endif