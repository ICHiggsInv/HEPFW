#include "AnalysisTools/Producers/interface/FilteredCollectionProducer.h"

using namespace std;

hepfw::FilteredCollectionProducer::FilteredCollectionProducer(){
  m_name        = "";
  m_inputLabel  = "";
  m_outputLabel = "";
}

hepfw::FilteredCollectionProducer::FilteredCollectionProducer(std::string name){
  m_name        = name;
  m_inputLabel  = "";
  m_outputLabel = "";
}

hepfw::FilteredCollectionProducer::FilteredCollectionProducer(std::string name,std::string inputLabel,std::string outputLabel){
  m_name        = name;
  m_inputLabel  = inputLabel;
  m_outputLabel = outputLabel;
}

hepfw::FilteredCollectionProducer::~FilteredCollectionProducer(){
  
}

void hepfw::FilteredCollectionProducer::produce(hepfw::Event &event){
  
}

void hepfw::FilteredCollectionProducer::setInputLabel(std::string inputLabel){
  m_inputLabel = inputLabel;
}

void hepfw::FilteredCollectionProducer::setOutputLabel(std::string outputLabel){
  m_outputLabel = outputLabel;
}
