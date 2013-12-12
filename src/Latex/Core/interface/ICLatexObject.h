#ifndef LATEX_CORE_ICLATEXOBJECT
#define LATEX_CORE_ICLATEXOBJECT

// C++ Included
#include <string>

class ICLatexObject {
public:
  
  ICLatexObject(){};

  virtual std::string toString(){return "";};
  void print();
  void saveAs(std::string fileName);
  
private:


};

#endif