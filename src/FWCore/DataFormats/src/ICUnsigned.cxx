#include "FWCore/DataFormats/interface/ICUnsigned.h"

ICUnsigned::ICUnsigned(){
  m_varType = kBool;  
}

ICUnsigned::ICUnsigned(unsigned input){
  m_varType = kBool;
  m_var     = input;
}

unsigned ICUnsigned::get(){return m_var;}
