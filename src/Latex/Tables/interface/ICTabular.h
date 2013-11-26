#ifndef LATEX_TABLES_ICTABULAR
#define LATEX_TABLES_ICTABULAR

// C++ Included
#include <string>
#include <vector>

class ICTabular {
public:

  void addRowAfter();
  void addRowBefore();
  
private:

  vector<ICTabularRow> m_rows;

};

#endif