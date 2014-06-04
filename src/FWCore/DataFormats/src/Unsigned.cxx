#include "FWCore/DataFormats/interface/ICUnsigned.h"

ICUnsigned::ICUnsigned(){
  m_varType = kUnsigned;  
}

ICUnsigned::ICUnsigned(unsigned input){
  m_varType = kUnsigned;
  m_var     = input;
}

unsigned ICUnsigned::get(){return m_var;}
