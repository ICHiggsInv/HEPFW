#ifndef FWCore_Framework_ParameterSet
#define FWCore_Framework_ParameterSet

// HEPFW includes
#include "Algorithm/DataTypes/interface/CheckStdContainer.h"
#include "FWCore/Parameters/interface/Parameter.h"
#include "Parameters/JSONParser/interface/json.h"

// BOOST includes
#include <boost/lexical_cast.hpp>

// C++ STD includes
#include <string>
#include <vector>
#include <iostream>

namespace hepfw{
  
  /***********************************************/
  /** \brief ParameterSet
   * 
   * ParameterSet
   ***********************************************/
  class ParameterSet {
  public:
    
    ParameterSet();
    ParameterSet(Json::Value pset);
    ~ParameterSet();

    // Getting parameters
    template<class T>             T                  getParameter      (std::string parameterName);
    template<class arg>           std::vector<arg>   getParameterVector(std::string parameterName);
    template<class key,class arg> std::map<key,arg>  getParameterMap   (std::string parameterName);
    
    // Getting parameter sets
    hepfw::ParameterSet getParameterSet(std::string parameterName);
    hepfw::ParameterSet getParameterSet(unsigned    index);
    
    // other methods
    bool                     isParameterDefined(std::string parameterName);
    unsigned                 size();
    std::vector<std::string> getParameterList();
    
  private:
    
    hepfw::Parameter m_pset;
  };

  //TODO: need protections on all this
  template<class T> 
  T ParameterSet::getParameter(std::string parameterName){
    //std::cout << "[hepfw::ParameterSet::getParameter] Attempting to get parameter: " << parameterName << std::endl;
    
    return hepfw::Parameter(m_pset[parameterName]).getParameter<T>();
  }

  //TODO: need protections on all this
  template<class arg>
  std::vector<arg> ParameterSet::getParameterVector(std::string parameterName){
    //std::cout << "[hepfw::ParameterSet::getParameter] Attempting to get parameter vector: " << parameterName << std::endl;
    
    hepfw::Parameter p(m_pset[parameterName]);
    
    std::vector<arg> out;
    for ( unsigned index = 0; index < p.size(); ++index ){
      out.push_back(hepfw::Parameter(p[index]).getParameter<arg>());
    }
    
    return out;
  }
  
  //TODO: need protections on all this
  template<class key,class arg> 
  std::map<key,arg> ParameterSet::getParameterMap(std::string parameterName){

    //std::cout << "[hepfw::ParameterSet::getParameter] Attempting to get parameter map: " << parameterName << std::endl;
    
    std::map<key,arg> out;
    
    hepfw::Parameter p(m_pset[parameterName]);
    
    Json::Value::Members thisMembers = p.getMemberNames();
    for(unsigned i=0; i<thisMembers.size(); i++){
      
      std::string s = thisMembers[i];
      key thisKey = boost::lexical_cast<key>(s);
      
      out[thisKey] = hepfw::Parameter(p[s]).getParameter<arg>();
    }
    
    return out;
  }
}

#endif
