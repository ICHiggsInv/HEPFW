#include "PostProcessing/Data/interface/ProcessedDataset.h"

// C++ STD includes
#include <iostream>

using namespace std;

hepfw::ProcessedDataset::ProcessedDataset(){
  this->init();
}

hepfw::ProcessedDataset::ProcessedDataset(std::string name){
  this->init();
  m_name = "";
}

void hepfw::ProcessedDataset::init(){
  m_name = "";
  m_type = "";
}

hepfw::ProcessedDataset::~ProcessedDataset(){
  
  // Closing files and cleaning memory
//   for(unsigned i=0; i<m_fileCollection.size();i++){
//     m_fileCollection[i]->Close();
//     delete m_fileCollection[i];
//   }
}

void hepfw::ProcessedDataset::setName(string value){
  m_name = value;
}

void hepfw::ProcessedDataset::setType(string value){
  m_type = value;
}

void hepfw::ProcessedDataset::setTagCollection(vector<string> value){
  m_tagCollection = value;
}

void hepfw::ProcessedDataset::setFileCollection(vector<hepfw::File*> value){
  m_fileCollection = value;
}

string hepfw::ProcessedDataset::getName(){
  return m_name;
}

string hepfw::ProcessedDataset::getType(){
  return m_type;
}

vector<string> hepfw::ProcessedDataset::getTagCollection(){
  return m_tagCollection;
}

vector<hepfw::File*> hepfw::ProcessedDataset::getFileCollection(){
  return m_fileCollection;
}

void hepfw::ProcessedDataset::addTag(string value){
  m_tagCollection.push_back(value);
}

void hepfw::ProcessedDataset::addFile(hepfw::File* value){
  m_fileCollection.push_back(value);
}

bool hepfw::ProcessedDataset::hasTag(string value){
  
  for(unsigned i=0; i<m_tagCollection.size(); i++){
    if(value==m_tagCollection[i]){return true;}
  }

  return false;
}

TH1* hepfw::ProcessedDataset::getTH1(string path){
  
  cout << "[hepfw::ProcessedDataset::getTH1] Called with parameters path="<<path<<endl;
  
  TH1* hOut = 0;
  
  // Protecting against 0 file datasets
  if(m_fileCollection.size()==0){return hOut;}
  
  // Getting first histogram and cloning it 
  hOut = (TH1*) m_fileCollection[0]->Get(path.c_str())->Clone();
  
  for(unsigned i=1; i<m_fileCollection.size(); i++){
    hOut->Add( (TH1*) m_fileCollection[i]->Get(path.c_str()) );
  }
  
  return hOut;
}
