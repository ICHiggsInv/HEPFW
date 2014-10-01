#include "Latex/Table/interface/LatexTabularRow.h"

using namespace std;

#include <iostream>

hepfw::LatexTabularRow::LatexTabularRow(unsigned nCell){
  
  for(unsigned i=0; i<nCell; i++){push_back(hepfw::LatexTabularCell());}
  
}

string hepfw::LatexTabularRow::toString(){
  
  string out="";
  
  for(unsigned i=0; i<size(); i++){
    out += operator[](i).toString();  
    
    if(i+1 == size()){out += " \\\\\n";}
    else             {out += " & ";}
  }
  
  return out;
}