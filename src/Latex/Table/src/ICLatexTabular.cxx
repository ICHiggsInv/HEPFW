#include "Latex/Table/interface/ICLatexTabular.h"

#include <iostream>

using namespace std;

ICLatexTabular::ICLatexTabular(int nRow,int nCol){
  
  init();
  
  if(nRow<1 || nCol<1){cout << "ERROR: tabular size needs to be bigger than 1 in columns or rows!" << endl;}
  
  for(int a=0; a<nRow; a++){
    m_rows           .push_back(ICLatexTabularRow(nCol));
    m_rowsDecoration .push_back("");
  }
  m_rowsDecoration.push_back("");
  
  for(int b=0; b<nCol; b++){     
    m_columnAlignment .push_back("c");
    m_columnDecoration.push_back(""); 
  }
  m_columnDecoration.push_back("");  
  
  
}

void ICLatexTabular::init(){
  
  m_name = "tabular";
  
}

void ICLatexTabular::setCellContent(int iRow,int iCol,bool value){
  
  if(isCoordinateValid(iRow,iCol)){
    ((m_rows[iRow])[iCol]).setCellContent(value);
  }else{
    cout << "ERROR: Request tabular position is out of bounds." << endl;
  }
}

void ICLatexTabular::setCellContent(int iRow,int iCol,int value){
  
  if(isCoordinateValid(iRow,iCol)){
    ((m_rows[iRow])[iCol]).setCellContent(value);
  }else{
    cout << "ERROR: Request tabular position is out of bounds." << endl;
  }
}

void ICLatexTabular::setCellContent(int iRow,int iCol,unsigned value){
  
  if(isCoordinateValid(iRow,iCol)){
    ((m_rows[iRow])[iCol]).setCellContent(value);
  }else{
    cout << "ERROR: Request tabular position is out of bounds." << endl;
  }
}

void ICLatexTabular::setCellContent(int iRow,int iCol,float value){
  
  if(isCoordinateValid(iRow,iCol)){
    ((m_rows[iRow])[iCol]).setCellContent(value);
  }else{
    cout << "ERROR: Request tabular position is out of bounds." << endl;
  }
}

void ICLatexTabular::setCellContent(int iRow,int iCol,double value){
  
  if(isCoordinateValid(iRow,iCol)){
    ((m_rows[iRow])[iCol]).setCellContent(value);
  }else{
    cout << "ERROR: Request tabular position is out of bounds." << endl;
  }
}

void ICLatexTabular::setCellContent(int iRow,int iCol,const char* value){

  if(isCoordinateValid(iRow,iCol)){
    ((m_rows[iRow])[iCol]).setCellContent(string(value));
  }else{
    cout << "ERROR: Request tabular position is out of bounds." << endl;
  }  
}

void ICLatexTabular::setCellContent(int iRow,int iCol,string value){

  if(isCoordinateValid(iRow,iCol)){
    ((m_rows[iRow])[iCol]).setCellContent(value);
  }else{
    cout << "ERROR: Request tabular position is out of bounds." << endl;
  }
}

void ICLatexTabular::setCellPrecision(int iRow,int iCol,std::string value){

  if(isCoordinateValid(iRow,iCol)){
    ((m_rows[iRow])[iCol]).setCellPrecision(value);
  }else{
    cout << "ERROR: Request tabular position is out of bounds." << endl;
  }  
}

void ICLatexTabular::setCellColor(int iRow,int iCol,string value){
  
  if(isCoordinateValid(iRow,iCol)){
    ((m_rows[iRow])[iCol]).setCellColor(value);
    addRequiredPackage("xcolor");
  }else{
    cout << "ERROR: Request tabular position is out of bounds." << endl;
  }
}

void ICLatexTabular::setColumnDecorationBefore(int iCol,std::string value){
  
  if(iCol<0 || iCol>=int(m_rows[0].size())){
    cout << "ERROR: Request column position is out of bounds." << endl;
  }else{
    m_columnDecoration[iCol]=value;
  }
}

void ICLatexTabular::setColumnDecorationAfter (int iCol,std::string value){
  
  if(iCol<0 || iCol>=int(m_rows[0].size())){
    cout << "ERROR: Request column position is out of bounds." << endl;
  }else{
    m_columnDecoration[iCol+1]=value;
  }
}

void ICLatexTabular::setRowDecorationBefore(int iRow,std::string value){
  
  if(iRow<0 || iRow>=int(m_rows.size())){
    cout << "ERROR: Request row position is out of bounds." << endl;
  }else{
    m_rowsDecoration[iRow]=value;
  }
}

void ICLatexTabular::setRowDecorationAfter (int iRow,std::string value){
  
  if(iRow<0 || iRow>=int(m_rows.size())){  
    cout << "ERROR: Request row position is out of bounds." << endl;
  }else{
    m_rowsDecoration[iRow+1]=value;
  }
}

void ICLatexTabular::setTabularPrecision(std::string value){
 
  for(int iRow=0; iRow<int(m_rows.size()); iRow++){      
    for(int iCol=0; iCol<int(m_rows[0].size()); iCol++){
      ((m_rows[iRow])[iCol]).setCellPrecision(value);      
    }  
  }
}

string ICLatexTabular::toStringEnvBegin(){

  string out = getRequiredPackagesString();
  out += "\n";

  // Beginning environment
  out += "\\begin{"+m_name+"}";

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
  
string ICLatexTabular::toStringEnvInner(){

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

bool ICLatexTabular::isCoordinateValid(int iRow,int iCol){
  
  bool out = true;
  
  if(iCol<0 || iCol>=int(m_rows[0].size())){out=false;}
  if(iRow<0 || iRow>=int(m_rows   .size())){out=false;}

  return out;
}