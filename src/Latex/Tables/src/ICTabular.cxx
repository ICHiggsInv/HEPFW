#include "Latex/Tables/interface/ICTabular.h"

#include <iostream>

using namespace std;

ICTabular::ICTabular(int nCol, int nRow){
  
  init();
  
  if(nCol<1 || nRow<1){cout << "ERROR: tabular size needs to be bigger than 1 in columns or rows!" << endl;}
  
  for(int a=0; a<nRow; a++){
    m_rows.push_back(ICTabularRow(nCol));
    m_rowsDecoration.push_back("");
  }
  
  for(int b=0; b<nCol; b++){     
    m_columnDecoration.push_back(""); 
  }
  
  m_rowsDecoration  .push_back("");
  m_columnDecoration.push_back("");  
  
}

void ICTabular::init(){
  
  m_name = "tabular";
  
}

void ICTabular::set(int iCol,int iRow,string value){
  
  if(iCol<0 || iCol>=int(m_rows[0].size())){
    cout << "ERROR: Request tabular position is out of bounds in columns." << endl;
    return;
  }
  
  if(iRow<0 || iRow>=int(m_rows.size())){
    cout << "ERROR: Request tabular position is out of bounds in rows." << endl;
    return; 
  }
  
  ((m_rows[iRow])[iCol]).set(value);
}
  
string ICTabular::toStringEnvInner(){
  
  string out = "";  

  cout << "Debug 01" << endl;  
  for(unsigned i=0; i<m_rows.size(); i++){
    out += m_rows[i].toString();
  }
  cout << "Debug 02" << endl;  
  
  return out;
  
}