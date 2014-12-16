// HEPFW includes
#include "FWCore/IO/interface/File.h"
#include "Latex/Table/interface/LatexTable.h"
#include "Latex/Table/interface/LatexTabular.h"
#include "Latex/Table/interface/LatexCaption.h"

// ROOT includes
#include "TList.h"
#include "TFile.h"
#include "TDirectory.h"
#include "TH1I.h"
#include "TH1D.h"

// C++ STD includes
#include <string>
#include <vector>
#include <stdint.h>
#include <iostream>
#include <fstream>
#include <sys/time.h>
#include <ctime>

using namespace std;

void doSequenceEventYields(vector<hepfw::File*> files, string name){
  
  vector<TH1D*> h;
  for(unsigned i=0; i<files.size(); i++){
    h.push_back( (TH1D*) files[i]->Get(Form("Sequences/%s/EventYield_Absolute",name.c_str())) );
  }
  
  hepfw::LatexTable tblEvYields;
  tblEvYields.setCentering(true);
  tblEvYields.setPosition("htp");
  tblEvYields.setLabel   (name);
  
  int nCuts = h[0]->GetNbinsX();
  
  hepfw::LatexTabular tabEvYields(nCuts+1,files.size()+1);
  tblEvYields.innerObjects.push_back(&tabEvYields);
  
  tabEvYields.setColumnAlignment(0,"l");
  tabEvYields.setTabularPrecision(".0");
  
  tabEvYields.setRowDecorationBefore(0,    "\\hline");
  tabEvYields.setRowDecorationBefore(1,    "\\hline \\hline");
  tabEvYields.setRowDecorationAfter (nCuts,"\\hline");
  
  for(unsigned i=0; i<files.size(); i++){
    tabEvYields.setCellContent(0,i+1,Form("\\rotatebox{90}{%s}",files[i]->GetName()));
    tabEvYields.setColumnDecorationAfter(i,"|");
  }
  
  tabEvYields.setColumnDecorationBefore(0,"|");
//   tabEvYields.setColumnDecorationAfter(files.size(),"|");
  
  for(int i=1; i<=nCuts; i++){
    for(unsigned b=0; b<h.size(); b++){
      tabEvYields.setCellContent(i,0,Form("%s",h[0]->GetXaxis()->GetBinLabel(i)));
      tabEvYields.setCellContent(i,b+1,h[b]->GetBinContent(i));
    }
  }
  
  hepfw::LatexCaption capEvYields("Stuff");
  tblEvYields.innerObjects.push_back(&capEvYields);
  
  tblEvYields.saveAs(Form("tabEvYields_%s.tex",name.c_str()));
}


//#################################################################################
//#################################################################################
//#################################################################################
int main(int argc, char *argv[]){
  
  //
  
  vector<hepfw::File*> files;
  
  files.push_back(new hepfw::File("DATA_MET-2012A-22Jan2013-v1.root","READ"));
  files.push_back(new hepfw::File("DATA_MET-2012B-22Jan2013-v1.root","READ"));
  files.push_back(new hepfw::File("DATA_MET-2012C-22Jan2013-v1.root","READ"));
  files.push_back(new hepfw::File("DATA_MET-2012D-22Jan2013-v1.root","READ"));

  files.push_back(new hepfw::File("DATA_VBF-Parked-2012B-22Jan2013-v1.root","READ"));
  files.push_back(new hepfw::File("DATA_VBF-Parked-2012C-22Jan2013-v1.root","READ"));
  files.push_back(new hepfw::File("DATA_VBF-Parked-2012D-22Jan2013-v1.root","READ"));
  
  TDirectory *d = (TDirectory*) files[0]->Get("Sequences");
  TList          *iList = d->GetListOfKeys();
  
  TIter iter(iList);
  while (TObject *obj = iter()){
    cout << "Name: " << obj->GetName() << endl;
    doSequenceEventYields(files,obj->GetName());
  }
//   doSequenceEventYields(vector<hepfw::File> files, string name)
  /*
  //  
  TH1D *hDATA_MET_2012A = (TH1D*) DATA_MET_2012A.Get("Modules/eventQualityFilter/eventQualityFilterCount");
  TH1D *hDATA_MET_2012B = (TH1D*) DATA_MET_2012B.Get("Modules/eventQualityFilter/eventQualityFilterCount");
  TH1D *hDATA_MET_2012C = (TH1D*) DATA_MET_2012C.Get("Modules/eventQualityFilter/eventQualityFilterCount");
  TH1D *hDATA_MET_2012D = (TH1D*) DATA_MET_2012D.Get("Modules/eventQualityFilter/eventQualityFilterCount");
  
  TH1D *hDATA_VBF_Parked_2012B = (TH1D*) DATA_VBF_Parked_2012B.Get("Modules/eventQualityFilter/eventQualityFilterCount");
  TH1D *hDATA_VBF_Parked_2012C = (TH1D*) DATA_VBF_Parked_2012C.Get("Modules/eventQualityFilter/eventQualityFilterCount");
  TH1D *hDATA_VBF_Parked_2012D = (TH1D*) DATA_VBF_Parked_2012D.Get("Modules/eventQualityFilter/eventQualityFilterCount");

  //
  TH1D *yieldDATA_MET_2012A        = (TH1D*) DATA_MET_2012A.Get("Sequences/electronMetSelection/EventYield_Absolute");
  TH1D *yieldDATA_MET_2012B        = (TH1D*) DATA_MET_2012B.Get("Sequences/electronMetSelection/EventYield_Absolute");
  TH1D *yieldDATA_MET_2012C        = (TH1D*) DATA_MET_2012C.Get("Sequences/electronMetSelection/EventYield_Absolute");
  TH1D *yieldDATA_MET_2012D        = (TH1D*) DATA_MET_2012D.Get("Sequences/electronMetSelection/EventYield_Absolute");
  
  TH1D *yieldDATA_VBF_Parked_2012B = (TH1D*) DATA_VBF_Parked_2012B.Get("Sequences/electronMetSelection/EventYield_Absolute");
  TH1D *yieldDATA_VBF_Parked_2012C = (TH1D*) DATA_VBF_Parked_2012C.Get("Sequences/electronMetSelection/EventYield_Absolute");
  TH1D *yieldDATA_VBF_Parked_2012D = (TH1D*) DATA_VBF_Parked_2012D.Get("Sequences/electronMetSelection/EventYield_Absolute");
  
  //####################################################################################
  
  hepfw::LatexTable tblEvYields;
  tblEvYields.setCentering(true);
  tblEvYields.setPosition("htp");
  tblEvYields.setLabel   ("tblEvYields");
  
  int nCuts = yieldDATA_MET_2012A->GetNbinsX();
  
  hepfw::LatexTabular tabEvYields(nCuts+1,8);
  tblEvYields.innerObjects.push_back(&tabEvYields);
  
  tabEvYields.setColumnAlignment(0,"l");
  tabEvYields.setTabularPrecision(".0");
  
  tabEvYields.setRowDecorationBefore(0,    "\\hline");
  tabEvYields.setRowDecorationBefore(1,    "\\hline \\hline");
  tabEvYields.setRowDecorationAfter (nCuts,"\\hline");
  
  tabEvYields.setCellContent(0,1,"\\rotatebox{90}{DATA_MET_2012A}");
  tabEvYields.setCellContent(0,2,"\\rotatebox{90}{DATA_MET_2012B}");
  tabEvYields.setCellContent(0,3,"\\rotatebox{90}{DATA_MET_2012C}");
  tabEvYields.setCellContent(0,4,"\\rotatebox{90}{DATA_MET_2012D}");
  tabEvYields.setCellContent(0,5,"\\rotatebox{90}{DATA_VBF_Parked_2012B}");
  tabEvYields.setCellContent(0,6,"\\rotatebox{90}{DATA_VBF_Parked_2012C}");
  tabEvYields.setCellContent(0,7,"\\rotatebox{90}{DATA_VBF_Parked_2012D}");
  
  tabEvYields.setColumnDecorationBefore(0,"|");
  tabEvYields.setColumnDecorationAfter(yieldDATA_MET_2012A->GetNbinsX(),"|");
  
  for(int i=0; i<8; i++){
    tabEvYields.setColumnDecorationAfter(i,"|");
  }
  
  for(int i=1; i<=yieldDATA_MET_2012A->GetNbinsX(); i++){
    tabEvYields.setCellContent(i,0,Form("%s",yieldDATA_MET_2012A->GetXaxis()->GetBinLabel(i)));
    
    tabEvYields.setCellContent(i,1,yieldDATA_MET_2012A       ->GetBinContent(i));
    tabEvYields.setCellContent(i,2,yieldDATA_MET_2012B       ->GetBinContent(i));
    tabEvYields.setCellContent(i,3,yieldDATA_MET_2012C       ->GetBinContent(i));
    tabEvYields.setCellContent(i,4,yieldDATA_MET_2012D       ->GetBinContent(i));
    tabEvYields.setCellContent(i,5,yieldDATA_VBF_Parked_2012B->GetBinContent(i));
    tabEvYields.setCellContent(i,6,yieldDATA_VBF_Parked_2012C->GetBinContent(i));
    tabEvYields.setCellContent(i,7,yieldDATA_VBF_Parked_2012D->GetBinContent(i));
  }
  
  hepfw::LatexCaption capEvYields("Stuff");
  tblEvYields.innerObjects.push_back(&capEvYields);
  
  tblEvYields.saveAs("tabEvYields.tex");
  
  cout << "DATA_MET_2012A        " << yieldDATA_MET_2012A       ->GetBinContent(yieldDATA_MET_2012A       ->GetNbinsX()) << endl;
  cout << "DATA_MET_2012B        " << yieldDATA_MET_2012B       ->GetBinContent(yieldDATA_MET_2012B       ->GetNbinsX()) << endl;
  cout << "DATA_MET_2012C        " << yieldDATA_MET_2012C       ->GetBinContent(yieldDATA_MET_2012C       ->GetNbinsX()) << endl;
  cout << "DATA_MET_2012D        " << yieldDATA_MET_2012D       ->GetBinContent(yieldDATA_MET_2012D       ->GetNbinsX()) << endl;
  
  cout << "DATA_VBF_Parked_2012B " << yieldDATA_VBF_Parked_2012B->GetBinContent(yieldDATA_VBF_Parked_2012B->GetNbinsX()) << endl;
  cout << "DATA_VBF_Parked_2012C " << yieldDATA_VBF_Parked_2012C->GetBinContent(yieldDATA_VBF_Parked_2012C->GetNbinsX()) << endl;
  cout << "DATA_VBF_Parked_2012D " << yieldDATA_VBF_Parked_2012D->GetBinContent(yieldDATA_VBF_Parked_2012D->GetNbinsX()) << endl;
  
  //####################################################################################
  
  hepfw::LatexTable tblEvQlyFilter;
  tblEvQlyFilter.setCentering(true);
  tblEvQlyFilter.setPosition("htp");
  tblEvQlyFilter.setLabel   ("tblEvQlyFilter");
  
  hepfw::LatexTabular tabEvQlyFilter(hDATA_MET_2012A->GetNbinsX()+2,8);
  //   tabular0.setTabularPrecision(".0");
  tblEvQlyFilter.innerObjects.push_back(&tabEvQlyFilter);
  tabEvQlyFilter.setColumnDecorationBefore(0,"|");
  tabEvQlyFilter.setColumnDecorationBefore(1,"||");
  tabEvQlyFilter.setColumnDecorationBefore(2,"|");
  tabEvQlyFilter.setColumnDecorationBefore(3,"|");
  tabEvQlyFilter.setColumnDecorationBefore(4,"|");
  tabEvQlyFilter.setColumnDecorationBefore(5,"||");
  tabEvQlyFilter.setColumnDecorationBefore(6,"|");
  tabEvQlyFilter.setColumnDecorationBefore(7,"|");
  tabEvQlyFilter.setColumnDecorationAfter (7,"|");
  
  tabEvQlyFilter.setColumnAlignment(0,"l");
  
  tabEvQlyFilter.setRowDecorationBefore(0,"\\hline");
  tabEvQlyFilter.setRowDecorationBefore(1,"\\hline \\hline");
  tabEvQlyFilter.setRowDecorationAfter(hDATA_MET_2012A->GetNbinsX(),"\\hline");
  tabEvQlyFilter.setRowDecorationAfter(hDATA_MET_2012A->GetNbinsX()+1,"\\hline");
  
  tabEvQlyFilter.setCellContent(0,0,"Filter");
  tabEvQlyFilter.setCellContent(0,1,"Prompt A");
  tabEvQlyFilter.setCellContent(0,2,"Prompt B");
  tabEvQlyFilter.setCellContent(0,3,"Prompt C");
  tabEvQlyFilter.setCellContent(0,4,"Prompt D");
  tabEvQlyFilter.setCellContent(0,5,"Parked B");
  tabEvQlyFilter.setCellContent(0,6,"Parked C");
  tabEvQlyFilter.setCellContent(0,7,"Parked D");

  int binCutEvQualityFilter = 0;
  for(int i=1; i<=yieldDATA_MET_2012A->GetNbinsX(); i++){
    if(yieldDATA_MET_2012A->GetXaxis()->GetBinLabel(i)==string("Event Quality Filters")){
      binCutEvQualityFilter=i;
      break;
    }
  }
  cout << "Bin for Event Quality Filters = " << binCutEvQualityFilter << endl;
  
  for(int i=1;i<9;i++){
    
    tabEvQlyFilter.setCellContent(i,0,hDATA_MET_2012A       ->GetXaxis()->GetBinLabel(i));
    tabEvQlyFilter.setCellContent(i,1,hDATA_MET_2012A       ->GetBinContent(i)*100/yieldDATA_MET_2012A       ->GetBinContent(binCutEvQualityFilter-1));
    tabEvQlyFilter.setCellContent(i,2,hDATA_MET_2012B       ->GetBinContent(i)*100/yieldDATA_MET_2012B       ->GetBinContent(binCutEvQualityFilter-1));
    tabEvQlyFilter.setCellContent(i,3,hDATA_MET_2012C       ->GetBinContent(i)*100/yieldDATA_MET_2012C       ->GetBinContent(binCutEvQualityFilter-1));
    tabEvQlyFilter.setCellContent(i,4,hDATA_MET_2012D       ->GetBinContent(i)*100/yieldDATA_MET_2012D       ->GetBinContent(binCutEvQualityFilter-1));
    tabEvQlyFilter.setCellContent(i,5,hDATA_VBF_Parked_2012B->GetBinContent(i)*100/yieldDATA_VBF_Parked_2012B->GetBinContent(binCutEvQualityFilter-1));
    tabEvQlyFilter.setCellContent(i,6,hDATA_VBF_Parked_2012C->GetBinContent(i)*100/yieldDATA_VBF_Parked_2012C->GetBinContent(binCutEvQualityFilter-1));
    tabEvQlyFilter.setCellContent(i,7,hDATA_VBF_Parked_2012D->GetBinContent(i)*100/yieldDATA_VBF_Parked_2012D->GetBinContent(binCutEvQualityFilter-1));
    
  }
  
  
  
  // WARNING: This assumes first cut is the filters!!!
  tabEvQlyFilter.setCellContent(hDATA_MET_2012A->GetNbinsX()+1,0,"Total");
  tabEvQlyFilter.setCellContent(hDATA_MET_2012A->GetNbinsX()+1,1,100-(yieldDATA_MET_2012A       ->GetBinContent(binCutEvQualityFilter)*100/yieldDATA_MET_2012A       ->GetBinContent(binCutEvQualityFilter-1)));
  tabEvQlyFilter.setCellContent(hDATA_MET_2012A->GetNbinsX()+1,2,100-(yieldDATA_MET_2012B       ->GetBinContent(binCutEvQualityFilter)*100/yieldDATA_MET_2012B       ->GetBinContent(binCutEvQualityFilter-1)));
  tabEvQlyFilter.setCellContent(hDATA_MET_2012A->GetNbinsX()+1,3,100-(yieldDATA_MET_2012C       ->GetBinContent(binCutEvQualityFilter)*100/yieldDATA_MET_2012C       ->GetBinContent(binCutEvQualityFilter-1)));
  tabEvQlyFilter.setCellContent(hDATA_MET_2012A->GetNbinsX()+1,4,100-(yieldDATA_MET_2012D       ->GetBinContent(binCutEvQualityFilter)*100/yieldDATA_MET_2012D       ->GetBinContent(binCutEvQualityFilter-1)));
  tabEvQlyFilter.setCellContent(hDATA_MET_2012A->GetNbinsX()+1,5,100-(yieldDATA_VBF_Parked_2012B->GetBinContent(binCutEvQualityFilter)*100/yieldDATA_VBF_Parked_2012B->GetBinContent(binCutEvQualityFilter-1)));
  tabEvQlyFilter.setCellContent(hDATA_MET_2012A->GetNbinsX()+1,6,100-(yieldDATA_VBF_Parked_2012C->GetBinContent(binCutEvQualityFilter)*100/yieldDATA_VBF_Parked_2012C->GetBinContent(binCutEvQualityFilter-1)));
  tabEvQlyFilter.setCellContent(hDATA_MET_2012A->GetNbinsX()+1,7,100-(yieldDATA_VBF_Parked_2012D->GetBinContent(binCutEvQualityFilter)*100/yieldDATA_VBF_Parked_2012D->GetBinContent(binCutEvQualityFilter-1)));
  
  hepfw::LatexCaption caption("Percentage of events in data failing each of the event quality filters. For the parked analysis we use prompt A and parked B, C and D datasets.");
  tblEvQlyFilter.innerObjects.push_back(&caption);
  
  tblEvQlyFilter.saveAs("tblEvQlyFilter.tex");
  
  //================================================================
  
  hepfw::LatexTable tblLaserFilter;
  tblEvQlyFilter.setCentering(true);
  tblEvQlyFilter.setPosition("htp");
  tblEvQlyFilter.setLabel   ("tblLaserFilter");
  
  hepfw::LatexTabular tabLaserFilter(3,8);
  tblLaserFilter.innerObjects.push_back(&tabLaserFilter);
  
  tabLaserFilter.setColumnDecorationBefore(0,"|");
  tabLaserFilter.setColumnDecorationBefore(1,"||");
  tabLaserFilter.setColumnDecorationBefore(2,"|");
  tabLaserFilter.setColumnDecorationBefore(3,"|");
  tabLaserFilter.setColumnDecorationBefore(4,"|");
  tabLaserFilter.setColumnDecorationBefore(5,"||");
  tabLaserFilter.setColumnDecorationBefore(6,"|");
  tabLaserFilter.setColumnDecorationBefore(7,"|");
  tabLaserFilter.setColumnDecorationAfter (7,"|");
  
  tabLaserFilter.setCellContent(0,0,"Filter");
  tabLaserFilter.setCellContent(0,1,"Prompt A");
  tabLaserFilter.setCellContent(0,2,"Prompt B");
  tabLaserFilter.setCellContent(0,3,"Prompt C");
  tabLaserFilter.setCellContent(0,4,"Prompt D");
  tabLaserFilter.setCellContent(0,5,"Parked B");
  tabLaserFilter.setCellContent(0,6,"Parked C");
  tabLaserFilter.setCellContent(0,7,"Parked D");
  
  tabLaserFilter.setColumnAlignment(0,"l");
  
  tabLaserFilter.setRowDecorationBefore(0,"\\hline");
  tabLaserFilter.setRowDecorationBefore(1,"\\hline \\hline");
  tabLaserFilter.setRowDecorationAfter (2,"\\hline");
  
  int binCutECALFilter = 0;
  for(int i=1; i<=yieldDATA_MET_2012A->GetNbinsX(); i++){
    if(yieldDATA_MET_2012A->GetXaxis()->GetBinLabel(i)==string("ECAL Laser Filter")){
      binCutECALFilter=i;
    break;
    }
  }
  cout << "Bin for ECAL Filter = " << binCutECALFilter << endl;
  
  int binCutHCALFilter = 0;
  for(int i=1; i<=yieldDATA_MET_2012A->GetNbinsX(); i++){
    if(yieldDATA_MET_2012A->GetXaxis()->GetBinLabel(i)==string("HCAL Laser Filter")){
      binCutHCALFilter=i;
      break;
    }
  }
  cout << "Bin for HCAL Filter = " << binCutHCALFilter << endl;
  
  // WARNING: This assumes first cut is the filters!!!
  tabLaserFilter.setCellContent(1,0,"HCAL Laser Filter");
  tabLaserFilter.setCellContent(1,1,100-(100*yieldDATA_MET_2012A       ->GetBinContent(binCutHCALFilter)/yieldDATA_MET_2012A       ->GetBinContent(binCutECALFilter-1)));
  tabLaserFilter.setCellContent(1,2,100-(100*yieldDATA_MET_2012B       ->GetBinContent(binCutHCALFilter)/yieldDATA_MET_2012B       ->GetBinContent(binCutECALFilter-1)));
  tabLaserFilter.setCellContent(1,3,100-(100*yieldDATA_MET_2012C       ->GetBinContent(binCutHCALFilter)/yieldDATA_MET_2012C       ->GetBinContent(binCutECALFilter-1)));
  tabLaserFilter.setCellContent(1,4,100-(100*yieldDATA_MET_2012D       ->GetBinContent(binCutHCALFilter)/yieldDATA_MET_2012D       ->GetBinContent(binCutECALFilter-1)));
  tabLaserFilter.setCellContent(1,5,100-(100*yieldDATA_VBF_Parked_2012B->GetBinContent(binCutHCALFilter)/yieldDATA_VBF_Parked_2012B->GetBinContent(binCutECALFilter-1)));
  tabLaserFilter.setCellContent(1,6,100-(100*yieldDATA_VBF_Parked_2012C->GetBinContent(binCutHCALFilter)/yieldDATA_VBF_Parked_2012C->GetBinContent(binCutECALFilter-1)));
  tabLaserFilter.setCellContent(1,7,100-(100*yieldDATA_VBF_Parked_2012D->GetBinContent(binCutHCALFilter)/yieldDATA_VBF_Parked_2012D->GetBinContent(binCutECALFilter-1)));
  
  tabLaserFilter.setCellContent(2,0,"ECAL+HCAL Laser Filter");
  tabLaserFilter.setCellContent(2,1,100-(100*yieldDATA_MET_2012A       ->GetBinContent(binCutECALFilter)/yieldDATA_MET_2012A       ->GetBinContent(binCutECALFilter-1)));
  tabLaserFilter.setCellContent(2,2,100-(100*yieldDATA_MET_2012B       ->GetBinContent(binCutECALFilter)/yieldDATA_MET_2012B       ->GetBinContent(binCutECALFilter-1)));
  tabLaserFilter.setCellContent(2,3,100-(100*yieldDATA_MET_2012C       ->GetBinContent(binCutECALFilter)/yieldDATA_MET_2012C       ->GetBinContent(binCutECALFilter-1)));
  tabLaserFilter.setCellContent(2,4,100-(100*yieldDATA_MET_2012D       ->GetBinContent(binCutECALFilter)/yieldDATA_MET_2012D       ->GetBinContent(binCutECALFilter-1)));
  tabLaserFilter.setCellContent(2,5,100-(100*yieldDATA_VBF_Parked_2012B->GetBinContent(binCutECALFilter)/yieldDATA_VBF_Parked_2012B->GetBinContent(binCutECALFilter-1)));
  tabLaserFilter.setCellContent(2,6,100-(100*yieldDATA_VBF_Parked_2012C->GetBinContent(binCutECALFilter)/yieldDATA_VBF_Parked_2012C->GetBinContent(binCutECALFilter-1)));
  tabLaserFilter.setCellContent(2,7,100-(100*yieldDATA_VBF_Parked_2012D->GetBinContent(binCutECALFilter)/yieldDATA_VBF_Parked_2012D->GetBinContent(binCutECALFilter-1)));
  
  hepfw::LatexCaption capLaserFilter("ECAL and HCAL quality filters");
  tblLaserFilter.innerObjects.push_back(&capLaserFilter);
  
  tblLaserFilter.saveAs("tblLaserFilter.tex");
  */
}
