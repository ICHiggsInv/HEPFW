#include "FWCore/Parameters/interface/Parameter.h"

using namespace std;

hepfw::Parameter::Parameter(){
  
}

hepfw::Parameter::Parameter(Json::Value m_pset) : Json::Value(m_pset){

}

hepfw::Parameter::~Parameter(){
  
}

// TODO: check is passing reference is better
// hepfw::Parameter hepfw::Parameter::operator[](string index){
//   return hepfw::Parameter(Json::Value::operator[](index));
// }
// 
// hepfw::Parameter hepfw::Parameter::operator[](int index){
//   return hepfw::Parameter(Json::Value::operator[](index));
// }
