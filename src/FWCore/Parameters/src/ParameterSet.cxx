#include "FWCore/Parameters/interface/ParameterSet.h"

using namespace std;

hepfw::ParameterSet::ParameterSet(){
  
}

hepfw::ParameterSet::ParameterSet(Json::Value pset){
  m_pset = hepfw::Parameter(pset);
}

hepfw::ParameterSet::~ParameterSet(){
  
}

hepfw::ParameterSet hepfw::ParameterSet::getParameterSet(std::string parameterName){
  return hepfw::ParameterSet(m_pset[parameterName]);
}

hepfw::ParameterSet hepfw::ParameterSet::getParameterSet(unsigned index){
  return hepfw::ParameterSet(m_pset[index]);
}

bool hepfw::ParameterSet::isParameterDefined(std::string parameterName){
  return m_pset.isMember(parameterName);
}

unsigned hepfw::ParameterSet::size(){
  return m_pset.size();
}

vector<string> hepfw::ParameterSet::getParameterList(){
  return m_pset.getMemberNames();
}