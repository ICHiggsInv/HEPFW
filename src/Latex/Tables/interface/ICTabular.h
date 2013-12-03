#ifndef LATEX_TABLES_ICTABULAR
#define LATEX_TABLES_ICTABULAR

#include "Latex/Core/interface/ICLatexEnvironment.h"
#include "Latex/Tables/interface/ICTabularRow.h"

// C++ Included
#include <string>
#include <vector>

class ICTabular : public ICLatexEnvironment {
public:

  ICTabular(int nCol=2, int nRow=2);
  
  void set(int iCol,int iRow,std::string value);
  
  
  
  //void addRowAfter (int index);
  //void addRowBefore(int index);
  
private:

  // Private methods
  void                init();
  virtual std::string toStringEnvInner();
    
  // Private variables
  std::vector<std::string>  m_columnAlignment;
  std::vector<std::string>  m_columnDecoration;
  std::vector<std::string>  m_rowsDecoration;
  std::vector<ICTabularRow> m_rows;
  
  
};

#endif