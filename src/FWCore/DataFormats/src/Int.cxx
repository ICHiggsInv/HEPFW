#include "FWCore/DataFormats/interface/Int.h"

rat::Int::Int(){
  m_varType = rat::kInt;  
}

rat::Int::Int(int input){
  m_varType = rat::kInt;
  m_var     = input;
}

int rat::Int::get(){return m_var;}
