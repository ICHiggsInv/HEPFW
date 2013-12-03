// TODO: Description

// ICTools includes
#include "Latex/Tables/interface/ICTable.h"
#include "Latex/Tables/interface/ICTabular.h"

// Standard libraries includes
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[]){

  ICTable table0;  
  table0.setCentering(true);
  table0.setLabel("tableTest01");

  ICTabular tabular0(2,2);
  
  tabular0.set(0,0,"1");
  tabular0.set(0,1,"2");
  tabular0.set(1,0,"3");
  tabular0.set(1,1,"3");
  
  table0.innerObjects.push_back(&tabular0);
  
  table0.saveAs("text0.tex");
  
  return 0;

}