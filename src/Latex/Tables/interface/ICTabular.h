#ifndef LATEX_TABLES_ICTABULAR
#define LATEX_TABLES_ICTABULAR

#include "Latex/Core/interface/ICLatexEnvironment.h"
#include "Latex/Tables/interface/ICTabularRow.h"

// C++ Included
#include <string>
#include <vector>

class ICTabular : public ICLatexEnvironment {
public:

  ICTabular(int nRow=2,int nCol=2);

  void set(int iRow,int iCol,bool        value);
  void set(int iRow,int iCol,int         value);
  void set(int iRow,int iCol,unsigned    value);
  void set(int iRow,int iCol,float       value);
  void set(int iRow,int iCol,double      value);
  void set(int iRow,int iCol,const char* value);
  void set(int iRow,int iCol,std::string value);

  void setColumnDecorationBefore(int iCol,std::string value);
  void setColumnDecorationAfter (int iCol,std::string value);

  void setRowDecorationBefore(int iRow,std::string value);
  void setRowDecorationAfter (int iRow,std::string value);
  
  //void addRowAfter (int index);
  //void addRowBefore(int index);
  
private:

  // Private methods
  void                init();
  virtual std::string toStringEnvBegin();
  virtual std::string toStringEnvInner();
  bool                isCoordinateValid(int iRow,int iCol);
  
  
  // Private variables
  std::vector<std::string>  m_columnAlignment;
  std::vector<std::string>  m_columnDecoration;
  std::vector<std::string>  m_rowsDecoration;
  std::vector<ICTabularRow> m_rows;
  
  
};

#endif