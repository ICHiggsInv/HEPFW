#include "AnalysisTools/CutFlows/interface/AnalysisCut.h"

using namespace std;

hepfw::AnalysisCut::AnalysisCut(){

}

hepfw::AnalysisCut::AnalysisCut(string name){
  m_name = name;
}

hepfw::AnalysisCut::~AnalysisCut(){
  
}

bool hepfw::AnalysisCut::evaluate(hepfw::Event &event){
  return false;
}

string hepfw::AnalysisCut::getName(){
  return m_name;
}

