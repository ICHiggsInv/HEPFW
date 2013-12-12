#include "FWCore/DataFormats/interface/ICInt.h"

ICInt::ICInt(){
  m_varType = kInt;  
}

ICInt::ICInt(int input){
  m_varType = kInt;
  m_var     = input;
}

int ICInt::get(){return m_var;}
