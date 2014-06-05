#include "FWCore/DataFormats/interface/Unsigned.h"

rat::Unsigned::Unsigned(){
  m_varType = rat::kUnsigned;  
}

rat::Unsigned::Unsigned(unsigned input){
  m_varType = rat::kUnsigned;
  m_var     = input;
}

unsigned rat::Unsigned::get(){return m_var;}
