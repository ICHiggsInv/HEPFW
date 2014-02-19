//

#include "TString.h"
#include "TFile.h"
#include "TList.h"
#include "TKey.h"

#include "TH1C.h"
#include "TH1S.h"
#include "TH1I.h"
#include "TH1F.h"
#include "TH1D.h"
#include "TProfile.h"

#include "TH2C.h"
#include "TH2S.h"
#include "TH2I.h"
#include "TH2F.h"
#include "TH2D.h"
#include "TProfile2D.h" 

#include "TH3C.h"
#include "TH3S.h"
#include "TH3I.h"
#include "TH3F.h"
#include "TH3D.h"
#include "TProfile3D.h"

#include "TCanvas.h"

#include <string>
#include <iostream>
#include <cstdlib>

using namespace std;

int main(int argc, char *argv[]){

  TString inputFile = "";
  string  outputDir = "";
  string  outputFileType = "png";  
  
  cout << "*================================================*" << endl;
  cout << "|                  icTFileToImg                  |" << endl;
  cout << "|                                                |" << endl;  
  cout << "| Program to export all histograms and canvas to |" << endl;
  cout << "| image file automatically.                      |" << endl;
  cout << "*================================================*" << endl;
  
  // If there are arguments process them
  if(argc>1){
    
    for (int i = 1; i < argc; i++){
      if(string(argv[i])=="-i" || string(argv[i])=="--inputFile"){
        inputFile = argv[i+1]; i++;
      }
      else if(string(argv[i])=="-o" || string(argv[i])=="--outputDir"){
        outputDir = argv[i+1]; i++;
      }
      else if(string(argv[i])=="-t" || string(argv[i])=="--outputFileType"){
        outputDir = argv[i+1]; i++;
      }
    }
  }
  
  vector<TDirectoryFile*>  dirs;
  vector<TH1*>             vHist;
  vector<TCanvas*>         vCanv; 
  
  int cTH1C       = 0;
  int cTH1S       = 0;
  int cTH1I       = 0;
  int cTH1F       = 0;
  int cTH1D       = 0;
  int cTProfile   = 0;

  int cTH2C       = 0;
  int cTH2S       = 0;
  int cTH2I       = 0;
  int cTH2F       = 0;
  int cTH2D       = 0;
  int cTProfile2D = 0;
  
  int cTH3C       = 0;
  int cTH3S       = 0;
  int cTH3I       = 0;
  int cTH3F       = 0;
  int cTH3D       = 0;
  int cTProfile3D = 0;

  int cCanv       = 0; 
  
  TFile *f = new TFile(inputFile);
  
  TDirectoryFile* d = f;
  
  dirs.push_back(d);  
  
  for(unsigned i=0; i<dirs.size(); i++){
  
    TDirectoryFile *iDir  = dirs[i];
    TList          *iList = iDir->GetListOfKeys();
    
    TIter iter(iList);
    while (TObject *obj = iter()){
            
      string className = obj->ClassName();
      
      if(className == "TKey"){
        
        TKey* key = (TKey*) obj; 
        string keyClassName = key->GetClassName();        
        
        if(keyClassName=="TDirectoryFile"){
          TDirectoryFile* dd = (TDirectoryFile*) f->Get(Form("%s/%s",dirs[i]->GetPath(),obj->GetName()));
          dirs.push_back(dd);
        }

        else if(keyClassName=="TH1C")      {cTH1C++;       vHist.push_back( (TH1*)   f->Get(Form("%s/%s",iDir->GetPath(),obj->GetName())));}
        else if(keyClassName=="TH1S")      {cTH1S++;       vHist.push_back( (TH1*)   f->Get(Form("%s/%s",iDir->GetPath(),obj->GetName())));}
        else if(keyClassName=="TH1I")      {cTH1I++;       vHist.push_back( (TH1*)   f->Get(Form("%s/%s",iDir->GetPath(),obj->GetName())));}
        else if(keyClassName=="TH1F")      {cTH1F++;       vHist.push_back( (TH1*)   f->Get(Form("%s/%s",iDir->GetPath(),obj->GetName())));}
        else if(keyClassName=="TH1D")      {cTH1D++;       vHist.push_back( (TH1*)   f->Get(Form("%s/%s",iDir->GetPath(),obj->GetName())));}
        else if(keyClassName=="TProfile")  {cTProfile++;   vHist.push_back( (TH1*)   f->Get(Form("%s/%s",iDir->GetPath(),obj->GetName())));}
        
        else if(keyClassName=="TH2C")      {cTH2C++;       vHist.push_back( (TH1*)   f->Get(Form("%s/%s",iDir->GetPath(),obj->GetName())));}
        else if(keyClassName=="TH2S")      {cTH2S++;       vHist.push_back( (TH1*)   f->Get(Form("%s/%s",iDir->GetPath(),obj->GetName())));}
        else if(keyClassName=="TH2I")      {cTH2I++;       vHist.push_back( (TH1*)   f->Get(Form("%s/%s",iDir->GetPath(),obj->GetName())));}
        else if(keyClassName=="TH2F")      {cTH2F++;       vHist.push_back( (TH1*)   f->Get(Form("%s/%s",iDir->GetPath(),obj->GetName())));}
        else if(keyClassName=="TH2D")      {cTH2D++;       vHist.push_back( (TH1*)   f->Get(Form("%s/%s",iDir->GetPath(),obj->GetName())));}
        else if(keyClassName=="TProfile2D"){cTProfile2D++; vHist.push_back( (TH1*)   f->Get(Form("%s/%s",iDir->GetPath(),obj->GetName())));}
        
        else if(keyClassName=="TH3C")      {cTH3C++;       vHist.push_back( (TH1*)   f->Get(Form("%s/%s",iDir->GetPath(),obj->GetName())));}
        else if(keyClassName=="TH3S")      {cTH3S++;       vHist.push_back( (TH1*)   f->Get(Form("%s/%s",iDir->GetPath(),obj->GetName())));}
        else if(keyClassName=="TH3I")      {cTH3I++;       vHist.push_back( (TH1*)   f->Get(Form("%s/%s",iDir->GetPath(),obj->GetName())));}
        else if(keyClassName=="TH3F")      {cTH3F++;       vHist.push_back( (TH1*)   f->Get(Form("%s/%s",iDir->GetPath(),obj->GetName())));}
        else if(keyClassName=="TH3D")      {cTH3D++;       vHist.push_back( (TH1*)   f->Get(Form("%s/%s",iDir->GetPath(),obj->GetName())));}
        else if(keyClassName=="TProfile3D"){cTProfile3D++; vHist.push_back( (TH1*)   f->Get(Form("%s/%s",iDir->GetPath(),obj->GetName())));}

        else if(keyClassName=="TCanvas")   {cCanv++;       vCanv.push_back( (TCanvas*) f->Get(Form("%s/%s",iDir->GetPath(),obj->GetName())));}
        
      }
    }
  }
  
  if(cTH1C)      {cout << "TH1C found: "       << cTH1C << endl;}
  if(cTH1S)      {cout << "TH1S found: "       << cTH1S << endl;}
  if(cTH1I)      {cout << "TH1I found: "       << cTH1I << endl;}
  if(cTH1F)      {cout << "TH1F found: "       << cTH1F << endl;}
  if(cTH1D)      {cout << "TH1D found: "       << cTH1D << endl;}
  if(cTProfile)  {cout << "TProfile found: "   << cTProfile << endl;}
  
  if(cTH2C)      {cout << "TH2C found: "       << cTH2C << endl;}
  if(cTH2S)      {cout << "TH2S found: "       << cTH2S << endl;}
  if(cTH2I)      {cout << "TH2I found: "       << cTH2I << endl;}
  if(cTH2F)      {cout << "TH2F found: "       << cTH2F << endl;}
  if(cTH2D)      {cout << "TH2D found: "       << cTH2D << endl;}
  if(cTProfile2D){cout << "TProfile2D found: " << cTProfile2D << endl;}
  
  if(cTH3C)      {cout << "TH3C found: "       << cTH3C << endl;}
  if(cTH3S)      {cout << "TH3S found: "       << cTH3S << endl;}
  if(cTH3I)      {cout << "TH3I found: "       << cTH3I << endl;}
  if(cTH3F)      {cout << "TH3F found: "       << cTH3F << endl;}
  if(cTH3D)      {cout << "TH3D found: "       << cTH3D << endl;}
  if(cTProfile3D){cout << "TProfile3D found: " << cTProfile3D << endl;}
  if(cCanv)      {cout << "TCanvas found: "    << cCanv << endl;}  
  
  for(unsigned i=0; i<vHist.size(); i++){
    
    TH1*   iHist  = vHist[i];
    string iName  = iHist->GetName();
    string iClass = iHist->ClassName();
    string iPath  = iHist->GetDirectory()->GetPath();
    
    // Subtracting file name from path and initial /
    int found = iPath.find(":");
    iPath.erase(0,found+2);
    
    TCanvas c;
    
    if(iClass=="TH1C"){
      TH1C* h = (TH1C*) iHist;
      h->Draw();
    }
    else if(iClass=="TH1S"){
      TH1S* h = (TH1S*) iHist;
      h->Draw();
    }
    else if(iClass=="TH1I"){
      TH1I* h = (TH1I*) iHist;
      h->Draw();
    }
    else if(iClass=="TH1F"){
      TH1F* h = (TH1F*) iHist;
      h->Draw();
    }
    else if(iClass=="TH1D"){
      TH1D* h = (TH1D*) iHist;
      h->Draw();
    }
    else if(iClass=="TProfile"){
      TProfile* h = (TProfile*) iHist;
      h->Draw();
    }
    
    
    else if(iClass=="TH2C"){
      TH2C* h = (TH2C*) iHist;
      h->Draw();
    }
    else if(iClass=="TH2S"){
      TH2S* h = (TH2S*) iHist;
      h->Draw();
    }
    else if(iClass=="TH2I"){
      TH2I* h = (TH2I*) iHist;
      h->Draw();
    }
    else if(iClass=="TH2F"){
      TH2F* h = (TH2F*) iHist;
      h->Draw();
    }
    else if(iClass=="TH2D"){
      TH2D* h = (TH2D*) iHist;
      h->Draw();
    }
    else if(iClass=="TProfile2D"){
      TProfile2D* h = (TProfile2D*) iHist;
      h->Draw();
    }
    
    else if(iClass=="TH3C"){
      TH3C* h = (TH3C*) iHist;
      h->Draw();
    }
    else if(iClass=="TH3S"){
      TH3S* h = (TH3S*) iHist;
      h->Draw();
    }
    else if(iClass=="TH3I"){
      TH3I* h = (TH3I*) iHist;
      h->Draw();
    }
    else if(iClass=="TH3F"){
      TH3F* h = (TH3F*) iHist;
      h->Draw();
    }
    else if(iClass=="TH3D"){
      TH3D* h = (TH3D*) iHist;
      h->Draw();
    }
    else if(iClass=="TProfile3D"){
      TProfile3D* h = (TProfile3D*) iHist;
      h->Draw();
    }
    
    // Calculating output path for histogram
    string outPath = ""; 
    if(outputDir!=""){outPath += outputDir+"/";}
    outPath += iPath;
    
    system(Form("mkdir -p %s",outPath.c_str()));
    
    c.SaveAs(Form("%s/%s.%s",outPath.c_str(),iName.c_str(),outputFileType.c_str()));
    
  }

  for(unsigned i=0; i<vCanv.size(); i++){
    
    TCanvas* iCanv  = vCanv[i];
    string   iName  = iCanv->GetName();
    string   iPath  = "";//= iCanv->GetDirectory()->GetPath();
    
    // Calculating output path for histogram
    string outPath = ""; 
    if(outputDir!=""){outPath += outputDir+"/";}
    outPath += iPath;
    
    system(Form("mkdir -p %s",outPath.c_str()));
    
    iCanv->SaveAs(Form("%s/%s.%s",outPath.c_str(),iName.c_str(),outputFileType.c_str()));    
    
  }
  
  
  return 0;
  
} 
