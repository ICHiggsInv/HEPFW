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
  
  void setCellContent(bool        value);
  void setCellContent(int         value);
  void setCellContent(unsigned    value);
  void setCellContent(float       value);
  void setCellContent(double      value);
  void setCellContent(std::string value);
  
  void        setCellPrecision(std::string precision);
  std::string getCellPrecision();  
  
  void        setCellColor(std::string color);
  std::string getCellColor();
  
  
  std::string toString();
  
  
private:
  
  ICDataType* m_data;
  std::string m_precision;
  std::string m_cellColor;
  
};

#endif