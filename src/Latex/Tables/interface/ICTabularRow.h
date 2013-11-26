#ifndef LATEX_TABLES_ICTABULARROW
#define LATEX_TABLES_ICTABULARROW

// C++ Included
#include <string>
#include <vector>

class ICTabularRow {
public:

  void addCellAfter();
  void addCellBefore();
  
private:

  vector<ICTabularCell> m_cells;

};

#endif