#include "Latex/Table/interface/LatexTabularRow.h"

using namespace std;

#include <iostream>

rat::LatexTabularRow::LatexTabularRow(unsigned nCell){
  
  for(unsigned i=0; i<nCell; i++){push_back(rat::LatexTabularCell());}
  
}

string rat::LatexTabularRow::toString(){
  
  string out="";
  
  for(unsigned i=0; i<size(); i++){
    out += operator[](i).toString();  
    
    if(i+1 == size()){out += " \\\\\n";}
    else             {out += " & ";}
  }
  
  return out;
}