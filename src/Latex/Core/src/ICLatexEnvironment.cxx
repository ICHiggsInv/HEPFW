#include "Latex/Core/interface/ICLatexEnvironment.h"

using namespace std;

ICLatexEnvironment::ICLatexEnvironment(){
  
  m_name      = "";
  m_position  = "";
  m_centering = false;
  
}

ICLatexEnvironment::~ICLatexEnvironment(){}
    
string ICLatexEnvironment::toString(){
  
  string out;
  out  = this->toStringEnvBegin();
  out += this->toStringEnvInner();
  out += this->toStringEnvEnd();
  
  return out;
  
}


string ICLatexEnvironment::toStringEnvBegin(){
  
  string out;
  out = "\\begin{"+m_name+"}";
  
  if(m_position != ""){
    out += "["+m_position+"]";
  }
  out += "\n";
  
  if(m_centering){out += "\\centering\n";}

  return out;
  
}

string ICLatexEnvironment::toStringEnvInner(){

  string out;
  for(unsigned i=0; i<innerObjects.size(); i++){
    out += innerObjects[i]->toString();
  }  
  return out;

}

string ICLatexEnvironment::toStringEnvEnd(){
  
  string out;
  out = "\\end{"+m_name+"}\n";
  return out;
  
}

void ICLatexEnvironment::setCentering(bool centering){m_centering=centering;}

void ICLatexEnvironment::setPosition(std::string option){m_position=option;}