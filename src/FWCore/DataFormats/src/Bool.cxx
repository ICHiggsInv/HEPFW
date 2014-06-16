#include "FWCore/DataFormats/interface/Bool.h"

rat::Bool::Bool(){
  m_varType = rat::kBool;  
}

rat::Bool::Bool(bool input){
  m_varType = rat::kBool;
  m_var     = input;
}

bool rat::Bool::get(){return m_var;}