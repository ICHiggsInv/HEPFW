#include "FWCore/Framework/interface/JobSetup.h"

using namespace std;

hepfw::JobSetup::JobSetup(){

}

hepfw::JobSetup::~JobSetup(){
  
}

void hepfw::JobSetup::setDirectorySequences(TDirectory* dir){
  m_dirSequences = dir;
}

void hepfw::JobSetup::setDirectoryModules  (TDirectory* dir){
  m_dirModules = dir;
}

void hepfw::JobSetup::setOutputFile(hepfw::File* file){
  m_outputFile = file;
}

TDirectory* hepfw::JobSetup::getDirectorySequences(){
  return m_dirSequences;
}

TDirectory* hepfw::JobSetup::getDirectoryModules(){
  return m_dirModules;
}

hepfw::File* hepfw::JobSetup::getOutputFile(){
  return m_outputFile;
}
