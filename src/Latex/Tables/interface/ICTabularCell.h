#ifndef LATEX_TABLES_ICTABULARCELL
#define LATEX_TABLES_ICTABULARCELL

#include "FWCore/DataFormats/interface/ICDataType.h"

// C++ Included
#include <string>
#include <vector>

class ICTabularCell {
public:

  ICTabularCell();  
  ICTabularCell(bool        value);
  ICTabularCell(int         value);  
  ICTabularCell(unsigned    value);
  ICTabularCell(float       value);
  ICTabularCell(double      value);  
  ICTabularCell(std::string value);
  
  ~ICTabularCell();
  
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