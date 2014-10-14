#include "FWCore/DataFormats/interface/Int.h"

hepfw::Int::Int(){
  m_varType = hepfw::kInt;  
}

hepfw::Int::Int(int input){
  m_varType = hepfw::kInt;
  m_var     = input;
}

int hepfw::Int::get(){return m_var;}
