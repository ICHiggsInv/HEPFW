#include "Latex/Core/interface/ICLatexObject.h"

#include <TString.h>

#include <stdio.h>
#include <iostream>

using namespace std;

void ICLatexObject::print(){
  cout << this->toString() << endl;
}

std::string ICLatexObject::toString(){
  return getRequiredPackagesString();
}

void ICLatexObject::saveAs(string fileName){
  
  FILE * pFile;
  pFile = fopen (fileName.c_str(),"w");
  fprintf (pFile,"%s\n",this->toString().c_str());
  
}

void ICLatexObject::addRequiredPackage(string packageName){
  m_requiredPackages.insert(packageName);
}

string ICLatexObject::getRequiredPackagesString(){
  
  string out="";
  
  for(set<string>::iterator i=m_requiredPackages.begin(); i!=m_requiredPackages.end(); ++i){
    out += Form("\\usepackage{%s}\n",(*i).c_str());
  }
  
  return out;
}

set<string> ICLatexObject::getRequiredPackages(){
  return m_requiredPackages;
}
  
