#include "FWCore/DataFormats/interface/ICString.h"

using namespace std;

ICString::ICString(){
  m_varType = kString;  
}

ICString::ICString(string input){
  m_varType = kString;
  m_var     = input;
}

string ICString::get(){return m_var;}
