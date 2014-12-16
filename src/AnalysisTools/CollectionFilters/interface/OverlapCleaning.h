#ifndef AnalysisTools_Filters_OverlapCleaning
#define AnalysisTools_Filters_OverlapCleaning

// HEPFW includes
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Modules/interface/ProducerModule.h"
#include "Algorithm/Geometric/interface/DeltaR.h"

// C++ STD includes
#include <string>
#include <vector>

namespace hepfw{
  
  /***********************************************/
  /** \brief OverlapCleaning 
   * 
   * OverlapCleaning
   ***********************************************/
  template <class CollectionToClean, class CollectionReference>
  class OverlapCleaning : public hepfw::ProducerModule {
  public:
    
    OverlapCleaning();
    OverlapCleaning(std::string name);
    OverlapCleaning(std::string name,hepfw::ParameterSet &pset);
    OverlapCleaning(std::string name,std::string labelCollectionToClean,std::string labelCollectionReference);
    ~OverlapCleaning();
    
    void produce(hepfw::Event &event);
    
    void setMinDeltaR               (double value);
    void setLabelCollectionToClean  (std::string label);
    void setLabelCollectionReference(std::string label);
    void setLabelCollectionOutput   (std::string label);
    void setReferenceIsCollection   (bool isCollection);
    
  private:
    
    void init();
    
  private:
    
    bool m_verbose;
    
    std::string m_labelCollectionToClean;
    std::string m_labelCollectionReference;
    std::string m_labelCollectionOutput;
    std::vector<CollectionToClean>   *m_collectionToClean;
    std::vector<CollectionReference> *m_collectionReference;
    
    bool   m_referenceIsCollection;
    double m_minDeltaR;
    
  };
}

template <class CollectionToClean, class CollectionReference>
hepfw::OverlapCleaning<CollectionToClean,CollectionReference>::OverlapCleaning(){
  
  this->init(); // Setting default values
  m_name = "";
}

template <class CollectionToClean, class CollectionReference>
hepfw::OverlapCleaning<CollectionToClean,CollectionReference>::OverlapCleaning(std::string name){
  
  this->init(); // Setting default values
  m_name = name;
}

template <class CollectionToClean, class CollectionReference>
hepfw::OverlapCleaning<CollectionToClean,CollectionReference>::OverlapCleaning(std::string name,hepfw::ParameterSet &pset){
  
  this->init(); // Setting default values
  m_name = name;
  
  m_labelCollectionToClean   = pset.getParameter<std::string>("labelCollectionToClean");
  m_labelCollectionReference = pset.getParameter<std::string>("labelCollectionReference");
  m_labelCollectionOutput    = pset.getParameter<std::string>("labelCollectionOutput");
  
  if(pset.isParameterDefined("verbose"))  {m_verbose = pset.getParameter<bool>("verbose");}
  if(pset.isParameterDefined("minDeltaR")){this->setMinDeltaR(pset.getParameter<double>("minDeltaR"));}
  
  if(m_verbose){
    
    printf("==> Initialising module: hepfw::OverlapCleaning\n");
    printf("labelCollectionToClean   : %s\n",m_labelCollectionToClean.c_str());
    printf("labelCollectionReference : %s\n",m_labelCollectionReference.c_str());
    printf("labelCollectionOutput    : %s\n",m_labelCollectionOutput.c_str());
    printf("minDeltaR                : %.2f\n",m_minDeltaR);
  }
}

template <class CollectionToClean, class CollectionReference>
hepfw::OverlapCleaning<CollectionToClean,CollectionReference>::OverlapCleaning(std::string name,std::string labelCollectionToClean,std::string labelCollectionReference){

  this->init(); // Setting default values
  m_name                     = name;
  m_labelCollectionToClean   = labelCollectionToClean;
  m_labelCollectionReference = labelCollectionReference;
}

template <class CollectionToClean, class CollectionReference>
void hepfw::OverlapCleaning<CollectionToClean,CollectionReference>::init(){
  
  m_labelCollectionToClean   = "";
  m_labelCollectionReference = "";
  m_labelCollectionOutput    = "";
  m_collectionToClean        = 0;
  m_collectionReference      = 0;
  m_referenceIsCollection    = true;
  m_minDeltaR                = 0;
}

template <class CollectionToClean, class CollectionReference>
hepfw::OverlapCleaning<CollectionToClean,CollectionReference>::~OverlapCleaning(){
  m_collectionToClean   = 0;
  m_collectionReference = 0;
}

template <class CollectionToClean, class CollectionReference>
void hepfw::OverlapCleaning<CollectionToClean,CollectionReference>::produce(hepfw::Event &event){
  
  m_collectionToClean = event.getByName< std::vector<CollectionToClean> >(m_labelCollectionToClean);
  std::vector<CollectionToClean> cleanCollection;
  
  // In the case we are cleaning a collection using a reference collection
  if(m_referenceIsCollection){
    
    m_collectionReference = event.getByName< std::vector<CollectionReference> >(m_labelCollectionReference);
    
    for(unsigned a=0; a<m_collectionToClean->size(); a++){
      
      bool objPassed = true;
      CollectionToClean *pA = &(*m_collectionToClean)[a];
      
      for(unsigned b=0; b<m_collectionReference->size(); b++){
        
        CollectionReference *pB = &(*m_collectionReference)[b];
        
        if(deltaR<CollectionToClean,CollectionReference>(*pA,*pB)<=m_minDeltaR){
          objPassed = false;
          break;
        }
      }
      
      if(objPassed){
        cleanCollection.push_back(*pA);
      }
    }
  }
  
  // In the case we are cleaning a collection using a reference object
  else{
    
    CollectionReference *pB = event.getByName<CollectionReference>(m_labelCollectionReference);
    
    for(unsigned a=0; a<m_collectionToClean->size(); a++){
      
      CollectionToClean *pA = &(*m_collectionToClean)[a];
      
      if(deltaR<CollectionToClean,CollectionReference>(*pA,*pB)>m_minDeltaR){
        cleanCollection.push_back(*pA);
      }
    }
  }
  
  event.addProduct< std::vector<CollectionToClean> >(m_labelCollectionOutput,cleanCollection);
  
}

template <class CollectionToClean, class CollectionReference>
void hepfw::OverlapCleaning<CollectionToClean,CollectionReference>::setMinDeltaR(double value){
  m_minDeltaR = value;
}

template <class CollectionToClean, class CollectionReference>
void hepfw::OverlapCleaning<CollectionToClean,CollectionReference>::setLabelCollectionToClean(std::string label){
  m_labelCollectionToClean = label;
}

template <class CollectionToClean, class CollectionReference>
void hepfw::OverlapCleaning<CollectionToClean,CollectionReference>::setLabelCollectionReference(std::string label){
  m_labelCollectionReference = label;
}

template <class CollectionToClean, class CollectionReference>
void hepfw::OverlapCleaning<CollectionToClean,CollectionReference>::setLabelCollectionOutput(std::string label){
  m_labelCollectionOutput = label;
}

template <class CollectionToClean, class CollectionReference>
void hepfw::OverlapCleaning<CollectionToClean,CollectionReference>::setReferenceIsCollection(bool isCollection){
  m_referenceIsCollection = isCollection;
}

#endif  
