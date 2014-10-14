#include "Histograms/Analysis/interface/HistogramDataToSimCompare.h"

#include <iostream>

using namespace std;

hepfw::HistogramDataToSimCompare::HistogramDataToSimCompare(){

  init();
  m_name     = "";
}

hepfw::HistogramDataToSimCompare::HistogramDataToSimCompare(std::string name){
  
  init();
  m_name     = name;
}

void hepfw::HistogramDataToSimCompare::init(){
  
  // Initialising pointers 
  m_data     = 0; 
  m_simStack = 0;
  m_legend   = 0;
  
  // Initialising flags
  m_doLogy                  = false;
  m_autoRangeYaxis          = true;
  m_autoRangeYaxisforceZero = false;
  m_autoOrderSimHistograms  = true;
  m_doRatioPlot             = false;
  m_doBlindData             = false;
}

hepfw::HistogramDataToSimCompare::~HistogramDataToSimCompare(){
  
  // Cleaning memory of internal member if defined
  if(m_legend!=0)  {delete m_legend;}  
  if(m_simStack!=0){delete m_simStack;}
  
  // Cleaning memory of owned histograms
  for(unsigned i=0; i<m_histOwned.size(); i++){delete m_histOwned[i];}
}

void hepfw::HistogramDataToSimCompare::addSimHistogram(TH1D *histogram, string name, bool passOwnership){

  m_histograms[name] = histogram;
  if(passOwnership){m_histOwned.push_back(histogram);}
}

void hepfw::HistogramDataToSimCompare::addDataHistogram(TH1D *histogram,bool passOwnership){
  
  m_data = histogram;
  if(passOwnership){m_histOwned.push_back(m_data);}

}

void hepfw::HistogramDataToSimCompare::setAutoRangeYaxis(bool value,bool forceZero){
  m_autoRangeYaxis          = value;
  m_autoRangeYaxisforceZero = forceZero;
}

void hepfw::HistogramDataToSimCompare::setAutoOrderSimHistograms(bool value){m_autoOrderSimHistograms=value;}

void hepfw::HistogramDataToSimCompare::setDoRatioPlot(bool value){m_doRatioPlot=value;}

void hepfw::HistogramDataToSimCompare::setLogy(bool value){m_doLogy=value;}    

void hepfw::HistogramDataToSimCompare::setBlindData(double low,double high){
  
  m_doBlindData   = true;
  m_BlindDataLow  = low; 
  m_BlindDataHigh = high;
}

void hepfw::HistogramDataToSimCompare::doBlindData(){
  
  if(m_data){
    
    int binLow  = m_data->FindBin(m_BlindDataLow);
    int binHigh = m_data->FindBin(m_BlindDataHigh);
    
    cout << "binLow  :" << binLow << endl;
    cout << "binHigh :" << binHigh << endl;
    
    for(int i=binLow; i<=binHigh; i++){
      m_data->SetBinContent(i,0);
      m_data->SetBinError(i,0);
    }
  }
}

TCanvas* hepfw::HistogramDataToSimCompare::draw(){
  
  TCanvas *c = new TCanvas();

  if(m_doBlindData){doBlindData();}
  
  if(m_legend!=0){delete m_legend;}
  m_legend = new TLegend(0.55,0.85,0.85,0.95);  
  m_legend->SetBorderSize(1);
  m_legend->AddEntry(m_data,"Data","LPE");  
  
  if(m_simStack!=0){delete m_simStack; }

  m_simStack = new THStack(m_name.c_str(),m_name.c_str());
  
  for(map<string,TH1D*>::iterator i=m_histograms.begin(); i!=m_histograms.end(); i++){
    
    TH1D* h = i->second;
    
    m_simStack->Add(h);
    m_legend->AddEntry(h,i->first.c_str(),"F");
  }
  
  c->cd();

  TPad* upper = nullptr;
  TPad* lower = nullptr;  
  if(m_doRatioPlot){
    upper = new TPad("upper","pad",0, 0.26 ,1 ,1);
    lower = new TPad("lower","pad",0, 0 ,1 ,0.26);
//     upper->SetBottomMargin(0.02);
    upper->Draw();
    upper->cd();    
  }
  
  if(m_doLogy && !m_doRatioPlot){c    ->SetLogy();}
  if(m_doLogy &&  m_doRatioPlot){upper->SetLogy();}  
  
  if(m_autoRangeYaxis){
    pair<double,double> rangeY = getAutoRangeYaxis();
    m_data    ->GetYaxis()->SetRangeUser(rangeY.first,rangeY.second);

    m_data    ->Draw("P0E1");
    m_simStack->Draw("HISTsame");
  }
  else{
    m_simStack->Draw("HIST");
  }
  
  m_data    ->Draw("P0E1same");
  m_legend  ->Draw();  
  
  c->Update();

  if(m_doRatioPlot){
    
    c->cd();
    lower->SetTopMargin(0.026);
    lower->SetBottomMargin(0.24);
    lower->Draw();
    lower->cd();
    lower->SetGridy();
    
    TH1D* num = (TH1D*) m_data->Clone(Form("%s_%s",m_name.c_str(),"num"));
    TH1D* den = 0;
    
    for(map<string,TH1D*>::iterator i=m_histograms.begin(); i!=m_histograms.end(); i++){
     
      if(!den){den = (TH1D*) i->second->Clone(Form("%s_%s",m_name.c_str(),"den"));}
      else    {den->Add(i->second);}
    }
    
    num->Add(den,-1.0);
    
    TH1D *ratio = (TH1D*) num->Clone();
    
    ratio->GetYaxis()->SetLabelSize(0.08);
    ratio->GetYaxis()->SetRangeUser(-2.0,2.0);
    ratio->Divide(den);
    ratio->Draw("E1");
    upper->cd();  
  }
  
  return c;
  
}

pair<double,double> hepfw::HistogramDataToSimCompare::getAutoRangeYaxis(){

  pair<double,double> range;
  double hMinNoZero = 0;
  double hMaxNoZero = 0;
  
  range.first  = m_data->GetBinContent(m_data->GetMinimumBin());
  range.second = m_data->GetBinContent(m_data->GetMaximumBin());

  for(int i=1; i<m_data->GetNbinsX()+1; i++){
    
    if(hMinNoZero!=0 && m_data->GetBinContent(i)!=0){
      if(hMinNoZero>m_data->GetBinContent(i)){hMinNoZero=m_data->GetBinContent(i);}
    }
    if(hMinNoZero==0 && m_data->GetBinContent(i)!=0){ 
      hMinNoZero=m_data->GetBinContent(i);
    }   
    
    if(hMaxNoZero!=0 && m_data->GetBinContent(i)!=0){
      if(hMaxNoZero<m_data->GetBinContent(i)){hMaxNoZero=m_data->GetBinContent(i);}
    }
    if(hMaxNoZero==0 && m_data->GetBinContent(i)!=0){ 
      hMaxNoZero=m_data->GetBinContent(i);
    }   
  }
  
  cout << "min (data) = " << range.first  << " non-zero = " << hMinNoZero << endl;  
  cout << "max (data) = " << range.second << " non-zero = " << hMaxNoZero << endl;
  
  
  for(map<string,TH1D*>::iterator i=m_histograms.begin(); i!=m_histograms.end(); i++){
    
    double hMin = i->second->GetBinContent(i->second->GetMinimumBin());
    double hMax = i->second->GetBinContent(i->second->GetMaximumBin());
    
    if(hMin < range.first ){range.first  = hMin;}
    if(hMax > range.second){range.second = hMax;}   

    for(int x=1; x<m_data->GetNbinsX()+1; x++){
      
      if(hMinNoZero!=0 && i->second->GetBinContent(x)!=0){
        if(hMinNoZero>i->second->GetBinContent(x)){hMinNoZero=i->second->GetBinContent(x);}
      }
      if(hMinNoZero==0 && i->second->GetBinContent(x)!=0){ 
        hMinNoZero=i->second->GetBinContent(x);
      }   
      
      if(hMaxNoZero!=0 && i->second->GetBinContent(x)!=0){
        if(hMaxNoZero<i->second->GetBinContent(x)){hMaxNoZero=i->second->GetBinContent(x);}
      }
      if(hMaxNoZero==0 && i->second->GetBinContent(x)!=0){ 
        hMaxNoZero=i->second->GetBinContent(x);
      }   
    }
  }

  cout << "min (global) = " << range.first  << " non-zero = " << hMinNoZero << endl;  
  cout << "max (global) = " << range.second << " non-zero = " << hMaxNoZero << endl;

  if(m_doLogy){

    cout << "Start calculation for range with logY" << endl; 
    
    bool   minDone = false; 
    double minBase = 1;
    while(!minDone){
            
      if     (minBase<=hMinNoZero && minBase*10>hMinNoZero){minDone=true;}
      else if(minBase <hMinNoZero && minBase*10<hMinNoZero){minBase=minBase*10;}
      else                                                 {minBase=minBase/10;}
    }

    cout << "Calculation for range with logY - min done" << endl;
    
    bool   maxDone = false; 
    double maxBase = 1;
    while(!maxDone){
      
      if     (maxBase>=hMaxNoZero && maxBase/10<hMaxNoZero){maxDone=true;}
      else if(maxBase> hMaxNoZero && maxBase/10>hMaxNoZero){maxBase=maxBase/10;}
      else                                                 {maxBase=maxBase*10;}
    }    

    cout << "Calculation for range with logY - max done" << endl;
    
    range.first  = minBase;    
    range.second = maxBase;
  }
  else{
    
    // Increasing
    if(!m_autoRangeYaxisforceZero){
      
      if(range.first>0){range.first = 0.7*range.first;}
      else             {range.first = 1.3*range.first;}
      
      if(range.second>0){range.second = 1.3*range.second;}
      else              {range.second = 0.7*range.second;}
       
    }
    else{
      
      if(range.first>=0 && range.second>=0){
        range.first  = 0;
        range.second = 1.3*range.second;        
      }
      else if(range.first<=0 && range.second<=0){
        range.first  = 1.3*range.first;
        range.second = 0;        
      }
      else{
        cout << "WARNING: Cannot force zero on y-axis. Range includes zero. (" << m_name << ")" << endl;
        if(range.first>0){range.first = 0.7*range.first;}
        else             {range.first = 1.3*range.first;}
        
        if(range.second){range.second = 1.3*range.second;}
        else            {range.second = 0.7*range.second;}
        
      }
    }
  }

  cout << "min (final) = " << range.first  << endl;  
  cout << "max (final) = " << range.second << endl;
  
  return range;
  
}