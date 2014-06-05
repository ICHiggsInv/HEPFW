#include "Latex/Core/interface/LatexEnvironment.h"

using namespace std;

rat::LatexEnvironment::LatexEnvironment(){
  
  m_name      = "";
  m_position  = "";
  m_centering = false;
  
}

rat::LatexEnvironment::~LatexEnvironment(){}

string rat::LatexEnvironment::toString(){
  
  string out;
  out  = this->toStringEnvBegin();
  out += this->toStringEnvInner();
  out += this->toStringEnvEnd();
  
  return out;
  
}

string rat::LatexEnvironment::toStringEnvBegin(){
  
  string out;
  out = "\\begin{"+m_name+"}";
  
  if(m_position != ""){
    out += "["+m_position+"]";
  }
  out += "\n";
  
  if(m_centering){out += "\\centering\n";}

  return out;
  
}

string rat::LatexEnvironment::toStringEnvInner(){

  string out;
  for(unsigned i=0; i<innerObjects.size(); i++){
    out += innerObjects[i]->toString();
  }  
  return out;

}

string rat::LatexEnvironment::toStringEnvEnd(){
  
  string out;
  out = "\\end{"+m_name+"}\n";
  return out;
  
}

void rat::LatexEnvironment::setCentering(bool centering){m_centering=centering;}

void rat::LatexEnvironment::setPosition(std::string option){m_position=option;}
