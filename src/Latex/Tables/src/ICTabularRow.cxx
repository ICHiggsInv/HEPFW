#include "Latex/Tables/interface/ICTabularRow.h"

using namespace std;

#include <iostream>

ICTabularRow::ICTabularRow(unsigned nCell){
  
  for(unsigned i=0; i<nCell; i++){push_back(ICTabularCell());}
  
}

string ICTabularRow::toString(){
  
  string out="";
  
  cout << size() << endl;
  
  for(unsigned i=0; i<size(); i++){
    out += operator[](i).toString();  
    
    if(i+1 == size()){out += " \\\\\n";}
    else             {out += " & ";}
  }
  
  return out;
}