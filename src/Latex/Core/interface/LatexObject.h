#ifndef LATEX_CORE_ICLATEXOBJECT
#define LATEX_CORE_ICLATEXOBJECT

// C++ Included
#include <string>
#include <set>

class ICLatexObject {
public:
  
  ICLatexObject(){};

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

#endif