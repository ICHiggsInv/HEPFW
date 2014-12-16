#ifndef AnalysisTools_Producers_METModifierObjectSubtraction
#define AnalysisTools_Producers_METModifierObjectSubtraction

// HEPFW includes
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Modules/interface/ProducerModule.h"
#include "Algorithm/Geometric/interface/DeltaR.h"

// C++ STD includes
#include <string>
#include <vector>

namespace hepfw{
  
  /***********************************************/
  /** \brief METModifierObjectSubtraction 
   * 
   * METModifierObjectSubtraction
   ***********************************************/
  template <class MET, class Objects>
  class METModifierObjectSubtraction : public hepfw::ProducerModule {
  public:
    
    METModifierObjectSubtraction();
    METModifierObjectSubtraction(std::string name);
    METModifierObjectSubtraction(std::string name,hepfw::ParameterSet &pset);
    ~METModifierObjectSubtraction();
    
    void produce(hepfw::Event &event);
    
  private:
    
    void init();
    
  private:
    
    bool m_verbose;
    
    std::string m_labelMet;
    std::string m_labelObjectsSubtract;
    std::string m_outputLabel;
    MET                  *m_met;
    std::vector<Objects> *m_objects;
  };
}

template <class MET, class Objects>
hepfw::METModifierObjectSubtraction<MET,Objects>::METModifierObjectSubtraction(){
  
  this->init(); // Setting default values
  m_name = "";
}

template <class MET, class Objects>
hepfw::METModifierObjectSubtraction<MET,Objects>::METModifierObjectSubtraction(std::string name){
  
  this->init(); // Setting default values
  m_name = name;
}

template <class MET, class Objects>
hepfw::METModifierObjectSubtraction<MET,Objects>::METModifierObjectSubtraction(std::string name,hepfw::ParameterSet &pset){
  
  this->init(); // Setting default values
  m_name = name;
  
  m_labelMet             = pset.getParameter<std::string>("labelMet");
  m_labelObjectsSubtract = pset.getParameter<std::string>("labelObjectsSubtract");
  m_outputLabel          = pset.getParameter<std::string>("outputLabel");
  
  if(pset.isParameterDefined("verbose"))  {m_verbose = pset.getParameter<bool>("verbose");}
  
  if(m_verbose){
    
    printf("==> Initialising module: hepfw::METModifierObjectSubtraction\n");
    printf("labelCollectionToClean : %s\n",m_labelMet.c_str());
    printf("labelObjectsSubtract   : %s\n",m_labelObjectsSubtract.c_str());
    printf("outputLabel            : %s\n",m_outputLabel.c_str());
  }
}

template <class MET, class Objects>
void hepfw::METModifierObjectSubtraction<MET,Objects>::init(){
  
  m_met     = 0;
  m_objects = 0;
  
  m_labelMet             = "";
  m_labelObjectsSubtract = "";
  m_outputLabel          = "";
}

template <class MET, class Objects>
hepfw::METModifierObjectSubtraction<MET,Objects>::~METModifierObjectSubtraction(){
  
}

template <class MET, class Objects>
void hepfw::METModifierObjectSubtraction<MET,Objects>::produce(hepfw::Event &event){
  
  m_met     = event.getByName< MET >                 (m_labelMet);
  m_objects = event.getByName< std::vector<Objects> >(m_labelObjectsSubtract);

  MET outMet = *m_met;
  ROOT::Math::PtEtaPhiEVector vecMet = m_met->vector();
  
  //std::cout << "vec MET pt=" << vecMet.pt() << " eta=" << vecMet.eta() << std::endl;
  
  for(unsigned i=0; i<m_objects->size(); i++){
    
    Objects *obj = &(*m_objects)[i];
    vecMet -= obj->vector();
    vecMet.SetEta(0.);
    //std::cout << "vec OBJ pt=" << obj->vector().pt() << " eta=" << obj->vector().eta() << std::endl;
    //std::cout << "vec MET pt=" << vecMet.pt() << " eta=" << vecMet.eta() << std::endl;
  }

  outMet.set_vector(vecMet);
  
  event.addProduct<MET>(m_outputLabel,outMet);
  
}

#endif  
