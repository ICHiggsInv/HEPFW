#ifndef AnalysisTools_EventFilters_DiobjectTransverseMassWindow
#define AnalysisTools_EventFilters_DiobjectTransverseMassWindow

// HEPFW includes
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Modules/interface/FilterModule.h"
#include "FWCore/Parameters/interface/ParameterSet.h"

// C++ STD includes
#include <algorithm>
#include <string>
#include <vector>

namespace hepfw{
  
//   template <class Product>
//   bool cmpObjPt(const Product &a,const Product &b){
//     return a.pt() < b.pt() ;
//   }
  
  template <class Product>
  bool cmpPtrObjPt(const Product *a,const Product *b){
    return a->pt() < b->pt() ;
  }
  
  /***********************************************/
  /** \brief DiobjectTransverseMassWindow 
   * 
   * DiobjectTransverseMassWindow
   ***********************************************/
  template <class ObjA,class ObjB>
  class DiobjectTransverseMassWindow : public hepfw::FilterModule {
  public:
    
    DiobjectTransverseMassWindow();
    DiobjectTransverseMassWindow(std::string name);
    DiobjectTransverseMassWindow(std::string name,hepfw::ParameterSet &pset);
    ~DiobjectTransverseMassWindow();
    
    bool filter(hepfw::Event &event);
    
    void setInputLabelA(std::string inputLabel);
    void setInputLabelB(std::string inputLabel);
    
    void setMinMass(double value);
    void setMaxMass(double value);
    
  private:
    
    void init();
    
  private:

    bool m_verbose;
    bool m_objA_isVector;
    bool m_objB_isVector;
    
    std::string m_inputLabelA;
    std::string m_inputLabelB;
    
    bool m_doMinMass; unsigned m_minMass;
    bool m_doMaxMass; unsigned m_maxMass;
    
  };
}

template <class ObjA,class ObjB>
hepfw::DiobjectTransverseMassWindow<ObjA,ObjB>::DiobjectTransverseMassWindow(){

  this->init(); // Setting default values
  m_name = "";
}

template <class ObjA,class ObjB>
hepfw::DiobjectTransverseMassWindow<ObjA,ObjB>::DiobjectTransverseMassWindow(std::string name){

  this->init(); // Setting default values
  m_name = name;
}

template <class ObjA,class ObjB>
hepfw::DiobjectTransverseMassWindow<ObjA,ObjB>::DiobjectTransverseMassWindow(std::string name,hepfw::ParameterSet &pset){
  
  this->init(); // Setting default values;
  m_name        = name;
  m_inputLabelA = pset.getParameter<std::string>("inputLabelA");
  m_inputLabelB = pset.getParameter<std::string>("inputLabelB");
  
  if(pset.isParameterDefined("verbose")) {m_verbose  = pset.getParameter<bool>("verbose");}
  
  if(pset.isParameterDefined("objA_isVector")){m_objA_isVector = pset.getParameter<bool>("objA_isVector");}
  if(pset.isParameterDefined("objB_isVector")){m_objB_isVector = pset.getParameter<bool>("objB_isVector");}
  
  if(pset.isParameterDefined("minMass")){this->setMinMass(pset.getParameter<unsigned>("minMass"));}
  if(pset.isParameterDefined("maxMass")){this->setMaxMass(pset.getParameter<unsigned>("maxMass"));}
  
  if(m_verbose){
    
    printf("==> Initialising module: hepfw::DiobjectTransverseMassWindow\n");
    printf("InputLabelA : %s\n",m_inputLabelA.c_str());
    printf("InputLabelB : %s\n",m_inputLabelB.c_str());
    if(m_doMinMass){printf("m_doMinMass : %d\n",m_minMass);}
    if(m_doMaxMass){printf("m_doMaxMass : %d\n",m_maxMass);}
  }
  
}

template <class ObjA,class ObjB>
void hepfw::DiobjectTransverseMassWindow<ObjA,ObjB>::init(){

  m_inputLabelA = "";
  m_inputLabelB = "";
  
  m_objA_isVector = true;
  m_objB_isVector = true;
  
  m_doMinMass   = false;
  m_doMaxMass   = false;
}

template <class ObjA,class ObjB>
hepfw::DiobjectTransverseMassWindow<ObjA,ObjB>::~DiobjectTransverseMassWindow(){

}

template <class ObjA,class ObjB>
bool hepfw::DiobjectTransverseMassWindow<ObjA,ObjB>::filter(hepfw::Event &event){
  
  ObjA *inA;
  ObjB *inB;

  //
  if(m_objA_isVector){
    std::vector<ObjA> *vec =  event.getByName< std::vector<ObjA> >(m_inputLabelA);
    
    if(vec->size()<1){return false;}
    
    std::vector<ObjA*> sortedObjects;
    for(unsigned i=0; i<vec->size(); i++){
      sortedObjects.push_back( &(*vec)[i] );
    }
    std::sort(sortedObjects.begin(),sortedObjects.end(),hepfw::cmpPtrObjPt<ObjA>);
    inA = sortedObjects[0];
  }
  else{
    inA = event.getByName<ObjA>(m_inputLabelA);
  }

  //
  if(m_objB_isVector){
    std::vector<ObjB> *vec =  event.getByName< std::vector<ObjB> >(m_inputLabelB);
    
    if(vec->size()<1){return false;}
    
    std::vector<ObjB*> sortedObjects;
    for(unsigned i=0; i<vec->size(); i++){
      sortedObjects.push_back( &(*vec)[i] );
    }
    std::sort(sortedObjects.begin(),sortedObjects.end(),hepfw::cmpPtrObjPt<ObjB>);
    inB = sortedObjects[0];
  }
  else{
    inB = event.getByName<ObjB>(m_inputLabelA);
  }
  
  double px     = inA->vector().px() + inB->vector().px();
  double py     = inA->vector().py() + inB->vector().py();
  double normaP = pow(px,2) + pow(py,2);
  double mass   = sqrt(pow(inA->vector().Et()+inB->vector().Et(),2) - normaP);
  
  if(m_doMinMass){if(mass<m_minMass){return false;}}
  if(m_doMaxMass){if(mass>m_maxMass){return false;}}
  return true;
}

template <class ObjA,class ObjB>
void hepfw::DiobjectTransverseMassWindow<ObjA,ObjB>::setMinMass(double value){
  m_doMinMass = true;
  m_minMass   = value;
}

template <class ObjA,class ObjB>
void hepfw::DiobjectTransverseMassWindow<ObjA,ObjB>::setMaxMass(double value){
  m_doMaxMass = true;
  m_maxMass   = value;
}

template <class ObjA,class ObjB>
void hepfw::DiobjectTransverseMassWindow<ObjA,ObjB>::setInputLabelA(std::string inputLabel){
  m_inputLabelA = inputLabel;
}

template <class ObjA,class ObjB>
void hepfw::DiobjectTransverseMassWindow<ObjA,ObjB>::setInputLabelB(std::string inputLabel){
  m_inputLabelB = inputLabel;
}

#endif 