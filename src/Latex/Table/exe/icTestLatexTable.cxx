// TODO: Description

// ICTools includes
#include "Latex/Table/interface/ICLatexTable.h"
#include "Latex/Table/interface/ICLatexTabular.h"
#include "Latex/Table/interface/ICLatexCaption.h"

// Standard libraries includes
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[]){

  ICLatexTable table0;  
  table0.setCentering(true);
  table0.setPosition("htp");
  table0.setLabel   ("tableTest01");

  ICLatexTabular tabular0(3,3);
  
  tabular0.setColumnDecorationBefore(0,"|");
  tabular0.setColumnDecorationBefore(1,"||");
  tabular0.setColumnDecorationBefore(2,"|");
  tabular0.setColumnDecorationAfter (2,"|");
  
  tabular0.setRowDecorationBefore(0,"\\hline");
  tabular0.setRowDecorationBefore(1,"\\hline \\hline");
  tabular0.setRowDecorationBefore(2,"\\hline");
  tabular0.setRowDecorationAfter (2,"\\hline");

  tabular0.set(0,0," ");
  tabular0.set(0,1,"A");
  tabular0.set(0,2,"B");
  tabular0.set(1,0,"X");
  tabular0.set(1,1,1);
  tabular0.set(1,2,2.);  
  tabular0.set(2,0,"Y");
  tabular0.set(2,1,3);
  tabular0.set(2,2,4);  

  table0.innerObjects.push_back(&tabular0);
  
  ICLatexCaption caption = ICLatexCaption("This is a table caption!");
  
  table0.innerObjects.push_back(&caption);
  
  table0.saveAs("text0.tex");
  
  return 0;

}