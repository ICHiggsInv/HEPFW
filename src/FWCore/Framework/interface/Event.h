#ifndef FWCore_Framework_Event
#define FWCore_Framework_Event

// HEPFW includes
#include "FWCore/Framework/interface/Dataset.h"

// ICHiggsTauTau
#include "DataFormats/ICHiggsTauTau/interface/GenParticle.h"
#include "DataFormats/ICHiggsTauTau/interface/Met.h"

// ROOT
#include "TTree.h"
#include "TBranchElement.h"

// C++ STD includes
#include <string>
#include <vector>
#include <set>
#include <iostream>

namespace hepfw{
  
  /***********************************************/
  /** \brief Event
   * 
   * Event
   ***********************************************/
  class Event {
    friend class EventProcessor;
  public:
    
    Event();
    Event(TTree* tree,Long64_t treeEventNumber);
    ~Event();
    
    void setDataset        (hepfw::Dataset *dataset);
    void setTreeEventNumber(Long64_t        treeEventNumber);
    void setTree           (TTree          *tree);
    
    const hepfw::Dataset* getDataset();
    
    template <class Product> 
    Product* getByName(std::string productName);
        
    const ic::Met* getPFMet();
    
  private:
    
    // Dataset information
    hepfw::Dataset *m_dataset;
    
    // Event quantities coming from file
//     ic::EventInfo                *m_eventInfo;       // eventInfo
//     std::vector<ic::PileupInfo>  *m_pileUpInfo;      // pileupInfo

    std::vector<ic::GenParticle> *m_genParticles;    // genParticles
//     std::vector<ic::GenParticle> *m_genParticlesTaus // genParticlesTaus
//     std::vector<ic::GenJet>      *m_genJet;          // genJets
//     ic::Met                      *m_genMet;          // pfMetGen
// 
// ic::TriggerObject
//     std::vector<ic::Tau>       *m_hltTaus      // hltTaus
//     std::vector<ic::Candidate> *m_l1ExtraMET   // l1extraMET
//     std::vector<ic::Candidate> *m_l1ExtraMuons // l1extraMuons
//     
//     std::vector<ic::Vertex>      *m_vertex    // vertices
//     std::vector<ic::Photon>      *m_photons;  // photons
//     std::vector<ic::Electron>    *m_electron; // electrons
//     std::vector<ic::Muon>        *m_muons;    // muonsPFlow
//     std::vector<ic::Tau>         *m_taus;     // taus
// ic::Jet
//     std::vector<ic::PFJet>       *m_jets;           // pfJetsPFlow
    ic::Met                      *m_pfMet;          // pfMet
//     ic::Met                      *m_pfMVAMet;       // pfMVAMet
//     ic::Met                      *m_pfMetType1;     // m_pfMetType1   (this is the one for analysis)
//     vector<ic::Met>              *m_pfMVAMetVector; // pfMVAMetVector
//     
//     ic::Candidate
// 
// pair<string,bool>
// pair<unsigned long,float>

    Long64_t                               m_treeEventNumber;
    TTree                                 *m_tree;
    std::map<std::string,TBranchElement*>  m_cachedBranches;
    
  };

}

template <class Product> Product* hepfw::Event::getByName(std::string productName){
  
  std::map<std::string,TBranchElement*>::iterator it = m_cachedBranches.find(productName);
  
  if(it != m_cachedBranches.end()){
    return (Product*) it->second->GetObject();
  }else{
    TBranchElement *productBranch = (TBranchElement*) m_tree->GetBranch(productName.c_str());
    
    if(productBranch == 0){
      std::cout << "[hepfw::Event::getByName] ERROR: Branch=" << productName << " not found..." << std::endl;
      return 0;
    }
  
    Int_t readBytes = productBranch->GetEntry(m_treeEventNumber);

    if      (readBytes == -1){
      std::cout << "[hepfw::Event::getByName] ERROR: There was an I/O error accessing branch=" << productName << "..." << std::endl;
      return 0;
    }
    else if (readBytes ==  0){
      std::cout << "[hepfw::Event::getByName] ERROR: Entry=" << m_treeEventNumber << " of branch" << productName << " not found..." << std::endl;
      return 0;
    }
    
    m_cachedBranches[productName] = productBranch;
  
    return (Product*) productBranch->GetObject();
  }
}

#endif 