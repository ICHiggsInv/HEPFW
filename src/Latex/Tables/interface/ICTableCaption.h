#ifndef LATEX_TABLES_ICTABLECAPTION
#define LATEX_TABLES_ICTABLECAPTION

#include "Latex/Core/interface/ICLatexObject.h"

// C++ Included
#include <string>

class ICTableCaption : public ICLatexObject {
public:

  ICTableCaption();
  ICTableCaption(const char* value);

  void       set(std::string value);
  
  std::string get();
  
  std::string toString();
  
private:

  std::string m_caption;
  
};

#endif