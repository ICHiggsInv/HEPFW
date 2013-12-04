#include "Latex/Tables/interface/ICTable.h"

using namespace std;

ICTable::ICTable(){
  
  init();
  
}

void ICTable::init(){
 
  m_name      = "table";
  m_label     = "";
  
}

string ICTable::toStringEnvInner(){
  
  string out;
  if(m_label != ""){out += "\\label("+m_label+")\n";}
    
  for(unsigned i=0; i<innerObjects.size(); i++){
    out += innerObjects[i]->toString();
  }
  
  return out;  
  
}

void ICTable::setLabel(string label){m_label=label;}