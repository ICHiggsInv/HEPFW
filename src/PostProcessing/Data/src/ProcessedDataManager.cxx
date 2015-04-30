#include "PostProcessing/Data/interface/ProcessedDataManager.h"

// HEPFW includes
#include "FWCore/IO/interface/File.h"

// C++ STD includes
#include <iostream>

using namespace std;

hepfw::ProcessedDataManager::ProcessedDataManager(){
  
}

hepfw::ProcessedDataManager::ProcessedDataManager(hepfw::ParameterSet pset){
  
  for(unsigned i=0; i<pset.size(); i++){
    
    // Getting this data
    hepfw::ParameterSet thisData = pset.getParameterSet(i);
    
    string nameData = thisData.getParameter<std::string>("name");
    
    cout << "=> Found data with name: " << nameData << endl;
    
    hepfw::ProcessedData iProcData(nameData);
    
    // Getting the processed datasets and looping over them
    hepfw::ParameterSet thisDataset = thisData.getParameterSet("datasets");
    
    for(unsigned a=0; a<thisDataset.size(); a++){
    
      hepfw::ParameterSet thisD = thisDataset.getParameterSet(a);
      
      string nameDataset = thisD.getParameter<std::string>("name");
      
      cout << "==> Found dataset with name: " << nameDataset << endl;
      
      hepfw::ProcessedDataset iProcDataset;    
      iProcDataset.setName          (thisD.getParameter<std::string>("name"));
      iProcDataset.setType          (thisD.getParameter<std::string>("type"));
      iProcDataset.setTagCollection (thisD.getParameterVector<std::string>("tags"));
      
      // Opening files
      vector<hepfw::File*> fileCollection;
      vector<string>       fileNames = thisD.getParameterVector<std::string>("files");
      
      for(unsigned iFile=0; iFile<fileNames.size(); iFile++){      
        cout << "===> Found files with name: " << fileNames[iFile] << endl;
        fileCollection.push_back(new hepfw::File(fileNames[iFile].c_str()));
      }
      
      iProcDataset.setFileCollection(fileCollection);
      
      iProcData.addDataset(iProcDataset);
    }

    m_dataMap[nameData] = iProcData;
  }
}

hepfw::ProcessedDataManager::~ProcessedDataManager(){
  
}

void hepfw::ProcessedDataManager::addData(std::string name,hepfw::ProcessedData data){
  
}

TH1* hepfw::ProcessedDataManager::getTH1_byDataName_byDatasetTag(string dataName,string datasetTag,string path){
  
  cout << "[hepfw::ProcessedDataManager::getTH1_byDataName_byDatasetTag] Called with parameters dataName="<<dataName<<" datasetTag="<<datasetTag<<" path="<<path<<endl;
  
  return m_dataMap[dataName].getTH1_byDatasetTag(datasetTag,path);
}

TH1* hepfw::ProcessedDataManager::getTH1_byDataName_byDatasetName(string dataName,string datasetName,string path){
  
  return m_dataMap[dataName].getTH1_byDatasetName(datasetName,path);
}

