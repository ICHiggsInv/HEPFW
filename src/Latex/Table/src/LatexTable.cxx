#include "Latex/Table/interface/LatexTable.h"

using namespace std;

/***********************************************/
/** Default constructor
 ***********************************************/
rat::LatexTable::LatexTable(){
  
  init();
  
}

void rat::LatexTable::init(){
 
  m_name      = "table";
  m_label     = "";
  
}

string rat::LatexTable::toStringEnvInner(){
  
  string out;
  if(m_label != ""){out += "\\label{"+m_label+"}\n";}
    
  for(unsigned i=0; i<innerObjects.size(); i++){
    out += innerObjects[i]->toString();
  }
  
  return out;  
  
}

void rat::LatexTable::setLabel(string label){m_label=label;}