#include "FWCore/Framework/interface/Dataset.h"

using namespace std;

hepfw::Dataset::Dataset(){

}

hepfw::Dataset::~Dataset(){

} 

void hepfw::Dataset::setCrossSection(double xsec){
  m_crossSection = xsec;
}

void hepfw::Dataset::setNEventsProcessed(unsigned nEvents){
  m_nProcessed = nEvents;
}

void hepfw::Dataset::setName(std::string name){
  m_name = name;
}

void hepfw::Dataset::setGroup(std::string group){
  m_group = group;
}

void hepfw::Dataset::setType(std::string type){
  m_type = type;
}

double hepfw::Dataset::getCrossSection(){
  return m_crossSection;
}

int hepfw::Dataset::getNEventsProcessed(){
  return m_nProcessed;
}

std::string hepfw::Dataset::getName(){
  return m_name;
}

std::string hepfw::Dataset::getGroup(){
  return m_group;
}

std::string hepfw::Dataset::getType(){
  return m_type;
}


