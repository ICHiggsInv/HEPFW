#include "FWCore/DataFormats/interface/Float.h"

rat::Float::Float(){
  m_varType = rat::kFloat;  
}

rat::Float::Float(float input){
  m_varType = rat::kFloat;
  m_var     = input;
}

float rat::Float::get(){return m_var;}
