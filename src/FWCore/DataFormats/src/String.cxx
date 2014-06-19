#include "FWCore/DataFormats/interface/String.h"

using namespace std;

rat::String::String(){
  m_varType = rat::kString;  
}

rat::String::String(string input){
  m_varType = rat::kString;
  m_var     = input;
}

string rat::String::get(){return m_var;}
