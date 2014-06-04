#include "Latex/Table/interface/ICLatexTabularRow.h"

using namespace std;

#include <iostream>

ICLatexTabularRow::ICLatexTabularRow(unsigned nCell){
  
  for(unsigned i=0; i<nCell; i++){push_back(ICLatexTabularCell());}
  
}

string ICLatexTabularRow::toString(){
  
  string out="";
  
  for(unsigned i=0; i<size(); i++){
    out += operator[](i).toString();  
    
    if(i+1 == size()){out += " \\\\\n";}
    else             {out += " & ";}
  }
  
  return out;
}