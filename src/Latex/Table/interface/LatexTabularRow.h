#ifndef LATEX_TABLES_LATEXTABULARROW
#define LATEX_TABLES_LATEXTABULARROW

#include "Latex/Table/interface/LatexTabularCell.h"

// C++ Included
#include <string>
#include <vector>

namespace hepfw{
  
  /***********************************************/
  /** \brief LaTeX Tabular Row
   * 
   * This class is an abstraction of a LaTeX tabular row of cells.
   * It allow easy manipulation of its contents.
   ***********************************************/
  class LatexTabularRow : public std::vector<hepfw::LatexTabularCell> {
  public:
    
    LatexTabularRow(unsigned nCell);
    
    //void addCellAfter (index int);
    //void addCellBefore(index int);
    
    std::string toString();
    
  private:
    
    
  };
  
}

#endif