#include "FWCore/DataFormats/interface/Float.h"

hepfw::Float::Float(){
  m_varType = hepfw::kFloat;  
}

hepfw::Float::Float(float input){
  m_varType = hepfw::kFloat;
  m_var     = input;
}

float hepfw::Float::get(){return m_var;}
