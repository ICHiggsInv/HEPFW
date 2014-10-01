#include "FWCore/DataFormats/interface/Double.h"

hepfw::Double::Double(){
  m_varType = hepfw::kDouble;  
}

hepfw::Double::Double(double input){
  m_varType = hepfw::kDouble;
  m_var     = input;
}

double hepfw::Double::get(){return m_var;}
