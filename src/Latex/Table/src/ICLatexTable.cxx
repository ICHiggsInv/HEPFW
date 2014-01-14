#include "Latex/Table/interface/ICLatexTable.h"

using namespace std;

ICLatexTable::ICLatexTable(){
  
  init();
  
}

void ICLatexTable::init(){
 
  m_name      = "table";
  m_label     = "";
  
}

string ICLatexTable::toStringEnvInner(){
  
  string out;
  if(m_label != ""){out += "\\label{"+m_label+"}\n";}
    
  for(unsigned i=0; i<innerObjects.size(); i++){
    out += innerObjects[i]->toString();
  }
  
  return out;  
  
}

void ICLatexTable::setLabel(string label){m_label=label;}