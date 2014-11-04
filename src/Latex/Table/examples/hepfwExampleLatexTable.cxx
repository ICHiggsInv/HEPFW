// TODO: Description

// HEPFW includes
#include "Latex/Table/interface/LatexTable.h"
#include "Latex/Table/interface/LatexTabular.h"
#include "Latex/Table/interface/LatexCaption.h"

// Standard libraries includes
#include <iostream>
#include <string>

using namespace std;

/***********************************************/
/** Example of usage of IC LaTeX table code
 ***********************************************/
int main(int argc, char *argv[]){

  hepfw::LatexTable table0;  
  table0.setCentering(true);
  table0.setPosition("htp");
  table0.setLabel   ("tableTest01");

  hepfw::LatexTabular tabular0(3,3);
  
  tabular0.setColumnDecorationBefore(0,"|");
  tabular0.setColumnDecorationBefore(1,"||");
  tabular0.setColumnDecorationBefore(2,"|");
  tabular0.setColumnDecorationAfter (2,"|");
  
  tabular0.setRowDecorationBefore(0,"\\hline");
  tabular0.setRowDecorationBefore(1,"\\hline \\hline");
  tabular0.setRowDecorationBefore(2,"\\hline");
  tabular0.setRowDecorationAfter (2,"\\hline");

  tabular0.setCellContent(0,0," ");
  tabular0.setCellContent(0,1,"A");
  tabular0.setCellContent(0,2,"B");
  tabular0.setCellContent(1,0,"X");
  tabular0.setCellContent(1,1,1);
  tabular0.setCellContent(1,2,2.);  
  tabular0.setCellContent(2,0,"Y");
  tabular0.setCellContent(2,1,3);
  tabular0.setCellContent(2,2,4);  

  table0.innerObjects.push_back(&tabular0);
  
  hepfw::LatexCaption caption("This is a table caption!");
  
  table0.innerObjects.push_back(&caption);
  
  table0.saveAs("text0.tex");
  
  return 0;

}