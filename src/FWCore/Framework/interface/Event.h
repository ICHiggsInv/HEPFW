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

// BOOST includes
#include <boost/any.hpp>

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
    void addProduct(std::string productName, Product &product);
    
    template <class Product>
    Product* getByName(std::string productName);
    
  private:
    
    // Dataset information
    hepfw::Dataset                   *m_dataset;
    TTree                            *m_tree;
    Long64_t                          m_treeEventNumber;
    std::map<std::string,boost::any>  m_products;
    
  };

}

template <class Product> void hepfw::Event::addProduct(std::string productName, Product &product){
  
  m_products[productName] = product;
}

template <class Product> Product* hepfw::Event::getByName(std::string productName){
  
  std::map<std::string,boost::any>::iterator it = m_products.find(productName);

  if(it != m_products.end()){
    return boost::any_cast<Product>(&it->second);
  }else{
    
    TBranchElement *productBranch = (TBranchElement*) m_tree->GetBranch(productName.c_str());
    
    if(productBranch == 0){
      std::cout << "[hepfw::Event::getByName] ERROR: Branch=" << productName << " not found..." << std::endl;
      return 0;
    }
    
    Product *p = new Product();
    productBranch->SetAddress(&p);
    
    Int_t readBytes = productBranch->GetEntry(m_treeEventNumber);
    
    productBranch->SetAddress(0);
    
    if      (readBytes == -1){
      std::cout << "[hepfw::Event::getByName] ERROR: There was an I/O error accessing branch=" << productName << "..." << std::endl;
      return 0;
    }
    else if (readBytes ==  0){
      std::cout << "[hepfw::Event::getByName] ERROR: Entry=" << m_treeEventNumber << " of branch" << productName << " not found..." << std::endl;
      return 0;
    }
    
    this->addProduct(productName,*p);
    delete p;
    
    return boost::any_cast<Product>(&m_products.find(productName)->second);
  }
}

#endif 