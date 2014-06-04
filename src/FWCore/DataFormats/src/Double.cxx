#include "FWCore/DataFormats/interface/ICDouble.h"

ICDouble::ICDouble(){
  m_varType = kDouble;  
}

ICDouble::ICDouble(double input){
  m_varType = kDouble;
  m_var     = input;
}

double ICDouble::get(){return m_var;}
