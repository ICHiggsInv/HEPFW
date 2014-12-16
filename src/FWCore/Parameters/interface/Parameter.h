#ifndef FWCore_Framework_Parameter
#define FWCore_Framework_Parameter

// HEPFW includes
#include "Parameters/JSONParser/interface/json.h"
#include "Algorithm/DataTypes/interface/CheckStdContainer.h"

// C++ STD includes
#include <string>
#include <iostream>

namespace hepfw{
  
  /***********************************************/
  /** \brief Parameter
   * 
   * Parameter
   ***********************************************/
  class Parameter : public Json::Value{
  public:
    
    Parameter();
    Parameter(Json::Value pset);
    ~Parameter();
    
    template<class T> T getParameter();
    
//     hepfw::Parameter operator[](std::string index);
//     hepfw::Parameter operator[](int         index);
    
    // Need to supraseed operator []
    
  private:
    
  };
  
  template<class T>
  T Parameter::getParameter(){
    
    //std::cout << "[hepfw::Parameter::getParameter] Getting generic parameter" << std::endl;
    
    if     (hepfw::is_std_vector<T>::value){std::cout << "Trying to get a vector" << std::endl;}
    else if(hepfw::is_std_map<T>::value)   {std::cout << "Trying to get a map"    << std::endl;}
    else                                   {std::cout << "Trying to get a ???"    << std::endl;}
      
    return T();
  }
  
  template<>
  inline bool Parameter::getParameter<bool>(){
    //std::cout << "[hepfw::Parameter::getParameter] Getting bool parameter: " << this->asBool() << std::endl;
    return this->asBool();
  }
  
  //
  template<>
  inline int Parameter::getParameter<int>(){
    //std::cout << "[hepfw::Parameter::getParameter] Getting int parameter: " << this->asInt() << std::endl;
    return this->asInt();
  }
  
  template<>
  inline unsigned Parameter::getParameter<unsigned>(){
    //std::cout << "[hepfw::Parameter::getParameter] Getting unsigned parameter: " << this->asUInt() << std::endl;
    return this->asUInt();
  }
  
  template<>
  inline float Parameter::getParameter<float>(){
    //std::cout << "[hepfw::Parameter::getParameter] Getting float parameter: " << this->asBool() << std::endl;
    return this->asFloat();
  }
  
  template<>
  inline double Parameter::getParameter<double>(){
    //std::cout << "[hepfw::Parameter::getParameter] Getting double parameter: " << this->asDouble() << std::endl;
    return this->asDouble();
  }
  
  template<>
  inline std::string Parameter::getParameter<std::string>(){
    //std::cout << "[hepfw::Parameter::getParameter] Getting string parameter: " << this->asString() << std::endl;
    return this->asString();
  }
  
}

#endif
