#include "AnalysisTools/EventFilters/interface/L1TAlgoFilter.h"

// C++ STD includes
#include <iostream>

using namespace std;

hepfw::L1TAlgoFilter::L1TAlgoFilter(){
  m_name = "";
}

hepfw::L1TAlgoFilter::L1TAlgoFilter(string name){
  m_name = name;
}

hepfw::L1TAlgoFilter::~L1TAlgoFilter(){
  
}

void hepfw::L1TAlgoFilter::addAlgo(std::string algoName,int firstRun,int lastRun){
  
  pair<int,int> runRange(firstRun,lastRun);
  m_l1tAlgo[algoName] = runRange;
}

bool hepfw::L1TAlgoFilter::filter(hepfw::Event &event){
  
  
  
}
