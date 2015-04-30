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
