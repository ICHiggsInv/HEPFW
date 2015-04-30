#include "Latex/Table/interface/LatexTable.h"

using namespace std;

/***********************************************/
/** Default constructor
 ***********************************************/
hepfw::LatexTable::LatexTable(){
  
  init();
  
}

void hepfw::LatexTable::init(){
 
  m_name      = "table";
  m_label     = "";
  
}

string hepfw::LatexTable::toStringEnvInner(){
  
  string out;
  if(m_label != ""){out += "\\label{"+m_label+"}\n";}
    
  for(unsigned i=0; i<innerObjects.size(); i++){
    out += innerObjects[i]->toString();
  }
  
  return out;  
  
}

void hepfw::LatexTable::setLabel(string label){m_label=label;}