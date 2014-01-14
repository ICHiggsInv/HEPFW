#include "FWCore/DataFormats/interface/ICFloat.h"

ICFloat::ICFloat(){
  m_varType = kFloat;  
}

ICFloat::ICFloat(float input){
  m_varType = kFloat;
  m_var     = input;
}

float ICFloat::get(){return m_var;}
