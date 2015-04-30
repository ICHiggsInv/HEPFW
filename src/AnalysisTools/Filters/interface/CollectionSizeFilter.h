#ifndef AnalysisTools_Filters_CollectionSizeFilter
#define AnalysisTools_Filters_CollectionSizeFilter

// HEPFW includes
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Modules/interface/FilterModule.h"
#include "FWCore/Parameters/interface/ParameterSet.h"

// C++ STD includes
#include <string>
#include <vector>
#include <iostream>

namespace hepfw{
  
  /***********************************************/
  /** \brief CollectionSizeFilter 
   * 
   * CollectionSizeFilter
   ***********************************************/
  template <class Product>
  class CollectionSizeFilter : public hepfw::FilterModule {
  public:
    
    CollectionSizeFilter();
    CollectionSizeFilter(std::string name);
    CollectionSizeFilter(std::string name,std::string inputLabel);
    CollectionSizeFilter(std::string name,hepfw::ParameterSet &pset);
    ~CollectionSizeFilter();
    
    bool filter(hepfw::Event &event);
    
    void setInputLabel(std::string inputLabel);
    
    void setMinN(int value);
    void setMaxN(int value);
    
  private:
    
    void init();
    
  private:

    bool m_verbose;

    std::string           m_inputLabel;
    std::vector<Product> *inProduct;

    bool m_doMinN; unsigned m_minN;
    bool m_doMaxN; unsigned m_maxN;
    
  };
}

template <class Product>
hepfw::CollectionSizeFilter<Product>::CollectionSizeFilter(){

  this->init(); // Setting default values
  m_name = "";
}

template <class Product>
hepfw::CollectionSizeFilter<Product>::CollectionSizeFilter(std::string name){

  this->init(); // Setting default values
  m_name = name;
}

template <class Product>
hepfw::CollectionSizeFilter<Product>::CollectionSizeFilter(std::string name,std::string inputLabel){

  this->init(); // Setting default values
  m_name       = name;
  m_inputLabel = inputLabel;
}

template <class Product>
hepfw::CollectionSizeFilter<Product>::CollectionSizeFilter(std::string name,hepfw::ParameterSet &pset){
  
  this->init(); // Setting default values;
  m_name       = name;
  m_inputLabel = pset.getParameter<std::string>("inputLabel");
  
  if(pset.isParameterDefined("verbose")) {m_verbose  = pset.getParameter<bool>("verbose");}
  
  if(pset.isParameterDefined("minN")){this->setMinN(pset.getParameter<unsigned>("minN"));}
  if(pset.isParameterDefined("maxN")){this->setMaxN(pset.getParameter<unsigned>("maxN"));}
  
  if(m_verbose){
    
    printf("==> Initialising module: hepfw::CollectionSizeFilter\n");
    printf("InputLabel : %s\n",m_inputLabel.c_str());
    if(m_doMinN){printf("m_doMinN   : %d\n",m_minN);}
    if(m_doMaxN){printf("m_doMaxN   : %d\n",m_maxN);}
  }
  
}

template <class Product>
void hepfw::CollectionSizeFilter<Product>::init(){
  m_inputLabel = "";
  inProduct    = 0;
  m_doMinN     = false;
  m_doMaxN     = false;
}

template <class Product>
hepfw::CollectionSizeFilter<Product>::~CollectionSizeFilter(){

}

template <class Product>
bool hepfw::CollectionSizeFilter<Product>::filter(hepfw::Event &event){
  
  //if(m_verbose){std::cout << "[hepfw::CollectionSizeFilter<Product>::filter] Method Called" << std::endl;}
  
  inProduct = event.getByName< std::vector<Product> >(m_inputLabel);
  
  if(m_doMinN){if(inProduct->size()<m_minN){return false;}}
  if(m_doMaxN){if(inProduct->size()>m_maxN){return false;}}
  return true;
  
}

template <class Product>
void hepfw::CollectionSizeFilter<Product>::setMinN(int value){
  m_doMinN = true;
  m_minN   = value;
}

template <class Product>
void hepfw::CollectionSizeFilter<Product>::setMaxN(int value){
  m_doMaxN = true;
  m_maxN   = value;
}

template <class Product>
void hepfw::CollectionSizeFilter<Product>::setInputLabel (std::string inputLabel){
  m_inputLabel = inputLabel;
}

#endif 