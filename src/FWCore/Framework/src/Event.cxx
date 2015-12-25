#include "FWCore/Framework/interface/Event.h"

using namespace std;

hepfw::Event::Event(){
  
}

hepfw::Event::Event(TTree* tree,Long64_t treeEventNumber){
  
  m_treeEventNumber = treeEventNumber;
  m_tree            = tree;
}

hepfw::Event::~Event(){

}

void  hepfw::Event::setDataset(hepfw::Dataset *dataset){
  m_dataset = dataset;
}

void hepfw::Event::setTreeEventNumber(Long64_t treeEventNumber){
  m_treeEventNumber = treeEventNumber;
}

void hepfw::Event::setTree(TTree *tree){
  m_tree = tree;
}

const hepfw::Dataset* hepfw::Event::getDataset(){
  return m_dataset;
}

void hepfw::Event::addWeight(string name,double weight){
  
  m_weights[name] = weight;
  
}

double hepfw::Event::getWeight(string name){
  
  auto it = m_weights.find(name);
  
  if(it != m_weights.end()){
    return it->second;
  }else{
    cout << "[hepfw::Event] ERROR: Not weight defined with name=" << name << endl;
    return 0;
  }
}

double hepfw::Event::getTotalWeight(){
  
  double totWeight=1;
  
  for(auto i=m_weights.begin(); i!=m_weights.end() ; i++){
    totWeight=totWeight * i->second;
  }
  
  return totWeight;
}
