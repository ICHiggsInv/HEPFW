#ifndef LATEX_CORE_LATEXOBJECT
#define LATEX_CORE_LATEXOBJECT

// C++ Included
#include <string>
#include <set>

namespace hepfw{
  
  /***********************************************/
  /** \brief 
   * 
   * 
   ***********************************************/
  class LatexObject {
  public:
    
    LatexObject(){};
    
    virtual std::string toString();
    void print();
    
    void saveAs(std::string fileName);
    
  protected:
    
    void                  addRequiredPackage (std::string packageName);
    std::set<std::string> getRequiredPackages();
    std::string           getRequiredPackagesString();
    
  private:
    
    std::set<std::string> m_requiredPackages;
    
  };
  
}

#endif