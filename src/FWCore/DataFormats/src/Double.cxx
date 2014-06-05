#include "FWCore/DataFormats/interface/Double.h"

rat::Double::Double(){
  m_varType = rat::kDouble;  
}

rat::Double::Double(double input){
  m_varType = rat::kDouble;
  m_var     = input;
}

double rat::Double::get(){return m_var;}
