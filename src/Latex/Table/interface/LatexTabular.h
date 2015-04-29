#ifndef LATEX_TABLES_LATEXTABULAR
#define LATEX_TABLES_LATEXTABULAR

#include "Latex/Core/interface/LatexEnvironment.h"
#include "Latex/Table/interface/LatexTabularRow.h"

// C++ Included
#include <string>
#include <vector>

namespace hepfw{
  
  /***********************************************/
  /** \brief LaTeX Tabular
   * 
   * This class allows creation and manipulation of a LaTeX tabular from C++
   * code. 
   ***********************************************/
  class LatexTabular : public LatexEnvironment {
  public:
    
    LatexTabular(int nRow=2,int nCol=2);
    
    void setCellContent  (int iRow,int iCol,bool        value);
    void setCellContent  (int iRow,int iCol,int         value);
    void setCellContent  (int iRow,int iCol,unsigned    value);
    void setCellContent  (int iRow,int iCol,float       value);
    void setCellContent  (int iRow,int iCol,double      value);
    void setCellContent  (int iRow,int iCol,const char* value);
    void setCellContent  (int iRow,int iCol,std::string value);
    void setCellPrecision(int iRow,int iCol,std::string value);
    void setCellColor    (int iRow,int iCol,std::string value);
    
    void setColumnDecorationBefore(int iCol,std::string value);
    void setColumnDecorationAfter (int iCol,std::string value);
    
    void setRowDecorationBefore(int iRow,std::string value);
    void setRowDecorationAfter (int iRow,std::string value);
    
    void setColumnAlignment(int iCol,std::string value);
    
    void setTabularColumnDecoration(std::string value);
    void setTabularRowDecoration   (std::string value);
    void setTabularPrecision       (std::string value);
    
    void deleteColumn(int columnNumber);
    void deleteRow   (int rowNumber);
    
    std::string getCellContent(int iRow,int iCol);
    
    int getNColumn();
    int getNRow();
        
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
    std::vector<hepfw::LatexTabularRow> m_rows;
    
    
  };
  
}

#endif