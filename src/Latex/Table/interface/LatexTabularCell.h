#ifndef LATEX_TABLES_LATEXTABULARCELL
#define LATEX_TABLES_LATEXTABULARCELL

#include "FWCore/DataFormats/interface/DataType.h"

// C++ Included
#include <string>
#include <vector>

namespace hepfw{
  
  /***********************************************/
  /** \brief LaTeX Tabular Cell
   * 
   * This class is an abstraction of a LaTeX tabular cell.
   * It allow easy manipulation of its contents and their
   * printing.
   ***********************************************/
  class LatexTabularCell {
  public:
    
    LatexTabularCell();  
    LatexTabularCell(bool        value);
    LatexTabularCell(int         value);  
    LatexTabularCell(unsigned    value);
    LatexTabularCell(float       value);
    LatexTabularCell(double      value);  
    LatexTabularCell(std::string value);
    
    ~LatexTabularCell();
    
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
    
    hepfw::DataType* m_data;
    std::string m_precision;
    std::string m_cellColor;
    
  };
  
}

#endif