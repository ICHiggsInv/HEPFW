#ifndef LATEX_TABLES_ICTABULARROW
#define LATEX_TABLES_ICTABULARROW

#include "Latex/Tables/interface/ICTabularCell.h"

// C++ Included
#include <string>
#include <vector>

class ICTabularRow : public std::vector<ICTabularCell> {
public:

  ICTabularRow(unsigned nCell);
  
  //void addCellAfter (index int);
  //void addCellBefore(index int);
  
  std::string toString();
  
private:


};

#endif