#include "Latex/Core/interface/LatexEnvironment.h"

using namespace std;

hepfw::LatexEnvironment::LatexEnvironment(){
  
  m_name      = "";
  m_position  = "";
  m_centering = false;
  
}

hepfw::LatexEnvironment::~LatexEnvironment(){}

string hepfw::LatexEnvironment::toString(){
  
  string out;
  out  = this->toStringEnvBegin();
  out += this->toStringEnvInner();
  out += this->toStringEnvEnd();
  
  return out;
  
}

string hepfw::LatexEnvironment::toStringEnvBegin(){
  
  string out;
  out = "\\begin{"+m_name+"}";
  
  if(m_position != ""){
    out += "["+m_position+"]";
  }
  out += "\n";
  
  if(m_centering){out += "\\centering\n";}

  return out;
  
}

string hepfw::LatexEnvironment::toStringEnvInner(){

  string out;
  for(unsigned i=0; i<innerObjects.size(); i++){
    out += innerObjects[i]->toString();
  }  
  return out;

}

string hepfw::LatexEnvironment::toStringEnvEnd(){
  
  string out;
  out = "\\end{"+m_name+"}\n";
  return out;
  
}

void hepfw::LatexEnvironment::setCentering(bool centering){m_centering=centering;}

void hepfw::LatexEnvironment::setPosition(std::string option){m_position=option;}
