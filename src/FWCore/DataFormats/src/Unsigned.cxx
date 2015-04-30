#include "FWCore/DataFormats/interface/Unsigned.h"

hepfw::Unsigned::Unsigned(){
  m_varType = hepfw::kUnsigned;  
}

hepfw::Unsigned::Unsigned(unsigned input){
  m_varType = hepfw::kUnsigned;
  m_var     = input;
}

unsigned hepfw::Unsigned::get(){return m_var;}
