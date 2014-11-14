#include "FWCore/Framework/interface/Event.h"

using namespace std;

hepfw::Event::Event(){
//   m_pfMet        = new ic::Met;
//   m_genParticles = new vector<ic::GenParticle>;
}

hepfw::Event::Event(TTree* tree,Long64_t treeEventNumber){
//   m_pfMet        = new ic::Met;
//   m_genParticles = new vector<ic::GenParticle>;
  
  m_treeEventNumber = treeEventNumber;
  m_tree            = tree;
}

hepfw::Event::~Event(){
//   delete m_pfMet;
//   delete m_genParticles;
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

const ic::Met* hepfw::Event::getPFMet(){
  return m_pfMet;
}