// TODO: Description

// ICTools includes
#include "Latex/Tables/interface/ICTable.h"

// Standard libraries includes
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[]){

  ICTable table1;
  
  table1.setCentering(true);
  table1.setLabel("tableTest01");
  table1.saveAs("text0.tex");
  
  return 0;

}