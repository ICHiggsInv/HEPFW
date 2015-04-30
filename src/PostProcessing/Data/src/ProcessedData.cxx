#include "PostProcessing/Data/interface/ProcessedData.h"

// C++ STD includes
#include <iostream>

using namespace std;

hepfw::ProcessedData::ProcessedData(){
  m_name="";
}

hepfw::ProcessedData::ProcessedData(string name){
  m_name=name;
}

hepfw::ProcessedData::~ProcessedData(){
  
}

void hepfw::ProcessedData::addDataset(hepfw::ProcessedDataset dataset){
  m_datasetMap[dataset.getName()] = dataset;
}

TH1* hepfw::ProcessedData::getTH1_byDatasetTag(string datasetTag, string path){
  
  cout << "[hepfw::ProcessedData::getTH1_byDatasetTag] Called with parameters datasetTag="<<datasetTag<<" path="<<path<<endl;
  
  TH1* hOut = 0;
  
  for(auto it=m_datasetMap.begin(); it!=m_datasetMap.end(); it++){
    
    if(it->second.hasTag(datasetTag)){
      if(hOut==0){hOut =    it->second.getTH1(path);}  // If this is the first histogram to be found get it
      else       {hOut->Add(it->second.getTH1(path));} // else add it to what we have
    }
  }
  return hOut;
}

TH1* hepfw::ProcessedData::getTH1_byDatasetName(string datasetName,string path){
  
  TH1* hOut = 0;
  
  // Getting iterator for the dataset
  auto pHist = m_datasetMap.find(datasetName);
  
  // Protecting for the case the dataset does not exist
  if(pHist==m_datasetMap.end()){return hOut;}
  
  // If dataset exists return the TH1
  return pHist->second.getTH1(path);
}
