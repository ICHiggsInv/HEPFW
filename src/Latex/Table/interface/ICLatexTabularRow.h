#ifndef LATEX_TABLES_ICLATEXTABULARROW
#define LATEX_TABLES_ICLATEXTABULARROW

#include "Latex/Table/interface/ICLatexTabularCell.h"

// C++ Included
#include <string>
#include <vector>

class ICLatexTabularRow : public std::vector<ICLatexTabularCell> {
public:

  ICLatexTabularRow(unsigned nCell);
  
  //void addCellAfter (index int);
  //void addCellBefore(index int);
  
  std::string toString();
  
private:


};

#endif