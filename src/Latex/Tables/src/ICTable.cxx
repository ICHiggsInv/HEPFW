#include "Latex/Tables/interface/ICTable.h"

using namespace std;

ICTable::ICTable(){
  
  init();
  
}

void ICTable::init(){
 
  m_name      = "table";
  m_centering = false;
  m_label     = "";
  
}

string ICTable::toStringEnvInner(){
  
  string out;
  if(m_centering){out += "\\centering\n";}
  if(m_label != ""){out += "\\label("+m_label+")\n";}
    
  for(unsigned i=0; i<innerObjects.size(); i++){
    out += innerObjects[i]->toString();
  }
  
  return out;  
  
}

void ICTable::setCentering(bool centering){m_centering=centering;}
void ICTable::setLabel(string label){m_label=label;}