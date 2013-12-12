#include "Latex/Tables/interface/ICTabular.h"

#include <iostream>

using namespace std;

ICTabular::ICTabular(int nRow,int nCol){
  
  init();
  
  if(nCol<1 || nRow<1){cout << "ERROR: tabular size needs to be bigger than 1 in columns or rows!" << endl;}
  
  for(int a=0; a<nRow; a++){
    m_rows           .push_back(ICTabularRow(nCol));
    m_columnAlignment.push_back("c");
    m_rowsDecoration .push_back("");
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

void ICTabular::set(int iRow,int iCol,bool value){
  
  if(isCoordinateValid(iRow,iCol)){
    ((m_rows[iRow])[iCol]).set(value);
  }else{
    cout << "ERROR: Request tabular position is out of bounds." << endl;
  }
}

void ICTabular::set(int iRow,int iCol,int value){
  
  if(isCoordinateValid(iRow,iCol)){
    ((m_rows[iRow])[iCol]).set(value);
  }else{
    cout << "ERROR: Request tabular position is out of bounds." << endl;
  }
}

void ICTabular::set(int iRow,int iCol,unsigned value){
  
  if(isCoordinateValid(iRow,iCol)){
    ((m_rows[iRow])[iCol]).set(value);
  }else{
    cout << "ERROR: Request tabular position is out of bounds." << endl;
  }
}

void ICTabular::set(int iRow,int iCol,float value){
  
  if(isCoordinateValid(iRow,iCol)){
    ((m_rows[iRow])[iCol]).set(value);
  }else{
    cout << "ERROR: Request tabular position is out of bounds." << endl;
  }
}

void ICTabular::set(int iRow,int iCol,double value){
  
  if(isCoordinateValid(iRow,iCol)){
    ((m_rows[iRow])[iCol]).set(value);
  }else{
    cout << "ERROR: Request tabular position is out of bounds." << endl;
  }
}

void ICTabular::set(int iRow,int iCol,const char* value){

  if(isCoordinateValid(iRow,iCol)){
    ((m_rows[iRow])[iCol]).set(string(value));
  }else{
    cout << "ERROR: Request tabular position is out of bounds." << endl;
  }  
}

void ICTabular::set(int iRow,int iCol,string value){

  if(isCoordinateValid(iRow,iCol)){
    ((m_rows[iRow])[iCol]).set(value);
  }else{
    cout << "ERROR: Request tabular position is out of bounds." << endl;
  }
}
  
void ICTabular::setColumnDecorationBefore(int iCol,std::string value){m_columnDecoration[iCol]=value;}

void ICTabular::setColumnDecorationAfter (int iCol,std::string value){m_columnDecoration[iCol+1]=value;}

void ICTabular::setRowDecorationBefore(int iRow,std::string value){m_rowsDecoration[iRow]=value;}

void ICTabular::setRowDecorationAfter (int iRow,std::string value){m_rowsDecoration[iRow+1]=value;}
  
string ICTabular::toStringEnvBegin(){
  
  string out;

  // Beginning environment
  out = "\\begin{"+m_name+"}";
  
  // Adding position options
  if(m_position != ""){
    out += "["+m_position+"]";
  }

  // Adding column aligment and decoration
  out += "{";
  for(unsigned i=0; i<m_columnAlignment.size(); i++){
    out += m_columnDecoration[i];
    out += m_columnAlignment[i];
    if(i==m_columnAlignment.size()-1){
      out += m_columnDecoration[i+1];  
    }
  }
  out += "}";
    
  out += "\n";
  
  // Adding centering options
  if(m_centering){out += "\\centering\n";}

  return out;
  
}
  
string ICTabular::toStringEnvInner(){
  
  string out = "";  
  
  for(unsigned i=0; i<m_rows.size(); i++){
    if(m_rowsDecoration[i]!=""){
      out += m_rowsDecoration[i]+"\n";  
    }
    out += m_rows[i].toString();
  }
  
  if(m_rowsDecoration[m_rows.size()]!=""){
    out += m_rowsDecoration[m_rows.size()]+"\n";
  }
  
  return out;  
}

bool ICTabular::isCoordinateValid(int iRow,int iCol){
  
  bool out = true;
  
  if(iCol<0 || iCol>=int(m_rows[0].size())){out=false;}
  if(iRow<0 || iRow>=int(m_rows   .size())){out=false;}

  return out;
}