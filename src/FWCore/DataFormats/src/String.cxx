#include "FWCore/DataFormats/interface/String.h"

using namespace std;

hepfw::String::String(){
  m_varType = hepfw::kString;  
}

hepfw::String::String(string input){
  m_varType = hepfw::kString;
  m_var     = input;
}

string hepfw::String::get(){return m_var;}
