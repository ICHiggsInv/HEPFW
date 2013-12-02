#include "Latex/Core/interface/ICLatexObject.h"

#include <stdio.h>
#include <iostream>

using namespace std;

void ICLatexObject::print(){
  cout << this->toString() << endl;
}

void ICLatexObject::saveAs(string fileName){
  
  FILE * pFile;
  pFile = fopen (fileName.c_str(),"w");
  fprintf (pFile,"%s\n",this->toString().c_str());
  
}

