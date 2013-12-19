#ifndef LATEX_TABLES_ICLATEXTABULARCELL
#define LATEX_TABLES_ICLATEXTABULARCELL

#include "FWCore/DataFormats/interface/ICDataType.h"

// C++ Included
#include <string>
#include <vector>

class ICLatexTabularCell {
public:

  ICLatexTabularCell();  
  ICLatexTabularCell(bool        value);
  ICLatexTabularCell(int         value);  
  ICLatexTabularCell(unsigned    value);
  ICLatexTabularCell(float       value);
  ICLatexTabularCell(double      value);  
  ICLatexTabularCell(std::string value);
  
  ~ICLatexTabularCell();
  
  void set(bool        value);
  void set(int         value);
  void set(unsigned    value);
  void set(float       value);
  void set(double      value);
  void set(std::string value);
  
  std::string toString();
  
  
private:
  
  ICDataType* m_data;

};

#endif