#include "FWCore/DataFormats/interface/Bool.h"

hepfw::Bool::Bool(){
  m_varType = hepfw::kBool;  
}

hepfw::Bool::Bool(bool input){
  m_varType = hepfw::kBool;
  m_var     = input;
}

bool hepfw::Bool::get(){return m_var;}