#include "FWCore/DataFormats/interface/ICBool.h"

ICBool::ICBool(){
  m_varType = kBool;  
}

ICBool::ICBool(bool input){
  m_varType = kBool;
  m_var     = input;
}

bool ICBool::get(){return m_var;}