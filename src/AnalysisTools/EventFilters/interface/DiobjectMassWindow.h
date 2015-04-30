#ifndef AnalysisTools_EventFilters_DiobjectMassWindow
#define AnalysisTools_EventFilters_DiobjectMassWindow

// HEPFW includes
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Modules/interface/FilterModule.h"
#include "FWCore/Parameters/interface/ParameterSet.h"

// C++ STD includes
#include <algorithm>
#include <string>
#include <vector>

namespace hepfw{
  
  template <class Product>
  bool cmpObjPt(const Product &a,const Product &b){
    return a.pt() < b.pt() ;
  }
  
  /***********************************************/
  /** \brief DiobjectMassWindow 
   * 
   * DiobjectMassWindow
   ***********************************************/
  template <class Product>
  class DiobjectMassWindow : public hepfw::FilterModule {
  public:
    
    DiobjectMassWindow();
    DiobjectMassWindow(std::string name);
    DiobjectMassWindow(std::string name,hepfw::ParameterSet &pset);
    ~DiobjectMassWindow();
    
    bool filter(hepfw::Event &event);
    
    void setInputLabel(std::string inputLabel);
    
    void setMinMass(double value);
    void setMaxMass(double value);
    
  private:
    
    void init();
    
  private:

    bool m_verbose;

    std::string           m_inputLabel;
    std::vector<Product> *inProduct;

    bool m_doMinMass; unsigned m_minMass;
    bool m_doMaxMass; unsigned m_maxMass;
    
  };
}

template <class Product>
hepfw::DiobjectMassWindow<Product>::DiobjectMassWindow(){

  this->init(); // Setting default values
  m_name = "";
}

template <class Product>
hepfw::DiobjectMassWindow<Product>::DiobjectMassWindow(std::string name){

  this->init(); // Setting default values
  m_name = name;
}

template <class Product>
hepfw::DiobjectMassWindow<Product>::DiobjectMassWindow(std::string name,hepfw::ParameterSet &pset){
  
  this->init(); // Setting default values;
  m_name       = name;
  m_inputLabel = pset.getParameter<std::string>("inputLabel");
  
  if(pset.isParameterDefined("verbose")) {m_verbose  = pset.getParameter<bool>("verbose");}
  
  if(pset.isParameterDefined("minMass")){this->setMinMass(pset.getParameter<unsigned>("minMass"));}
  if(pset.isParameterDefined("maxMass")){this->setMaxMass(pset.getParameter<unsigned>("maxMass"));}
  
  if(m_verbose){
    
    printf("==> Initialising module: hepfw::DiobjectMassWindow\n");
    printf("InputLabel : %s\n",m_inputLabel.c_str());
    if(m_doMinMass){printf("m_doMinMass : %d\n",m_minMass);}
    if(m_doMaxMass){printf("m_doMaxMass : %d\n",m_maxMass);}
  }
  
}

template <class Product>
void hepfw::DiobjectMassWindow<Product>::init(){

  m_inputLabel = "";
  inProduct    = 0;
  m_doMinMass  = false;
  m_doMaxMass  = false;
}

template <class Product>
hepfw::DiobjectMassWindow<Product>::~DiobjectMassWindow(){

}

template <class Product>
bool hepfw::DiobjectMassWindow<Product>::filter(hepfw::Event &event){
  
  inProduct = event.getByName< std::vector<Product> >(m_inputLabel);
  if(inProduct->size()<2){return false;}
  
  std::vector<Product> sortedObjects = *inProduct;
  std::sort(sortedObjects.begin(),sortedObjects.end(),hepfw::cmpObjPt<Product>);
  
  Product *p0 = &sortedObjects[0];
  Product *p1 = &sortedObjects[1];
  
  double px     = p0->vector().px() + p1->vector().px();
  double py     = p0->vector().py() + p1->vector().py();
  double pz     = p0->vector().pz() + p1->vector().pz();
  double normaP = pow(px,2) + pow(py,2) + pow(pz,2);
  double mass   = sqrt(pow(p0->energy()+p1->energy(),2) - normaP);
  
  if(m_doMinMass){if(mass<m_minMass){return false;}}
  if(m_doMaxMass){if(mass>m_maxMass){return false;}}
  return true;
}

template <class Product>
void hepfw::DiobjectMassWindow<Product>::setMinMass(double value){
  m_doMinMass = true;
  m_minMass   = value;
}

template <class Product>
void hepfw::DiobjectMassWindow<Product>::setMaxMass(double value){
  m_doMaxMass = true;
  m_maxMass   = value;
}

template <class Product>
void hepfw::DiobjectMassWindow<Product>::setInputLabel (std::string inputLabel){
  m_inputLabel = inputLabel;
}

#endif 