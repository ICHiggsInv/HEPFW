#include "Plots/Tools/interface/ICPlotCollection.h"

#include "TLegend.h"
#include "TH1F.h"
#include "TH1D.h"
#include "TH2F.h"
#include "TH2D.h"

using namespace std;

/********************************************//**
 * Constructor for this class
 ***********************************************/
template <class PlotIndex,class PlotType>
ICPlotCollection<PlotIndex,PlotType>::ICPlotCollection(){

  m_drawLegend=false;

}

template <class PlotIndex,class PlotType>
ICPlotCollection<PlotIndex,PlotType>::ICPlotCollection(map<PlotIndex,TFile*> samples,std::string path){
  
  
  for(typename map<PlotIndex,TFile*>::iterator i=samples.begin(); i!=samples.end(); i++){
    (*this)[i->first] = (PlotType*) i->second->Get(path.c_str());
  } 
}

template <class PlotIndex,class PlotType>
void ICPlotCollection<PlotIndex,PlotType>::setXaxisRangeUser(double min,double max){

  // Looping over plots
  for(typename map<PlotIndex,PlotType*>::iterator i=this->begin(); i!=this->end(); i++){
    i->second->GetXaxis()->SetRangeUser(min,max);
  }
}

template <class PlotIndex,class PlotType>
void ICPlotCollection<PlotIndex,PlotType>::setXaxisTitle(std::string title){

  // Looping over plots
  for(typename map<PlotIndex,PlotType*>::iterator i=this->begin(); i!=this->end(); i++){
    i->second->GetXaxis()->SetTitle(title.c_str());
  }
}

template <class PlotIndex,class PlotType>
void ICPlotCollection<PlotIndex,PlotType>::setYaxisRangeUser(double min,double max){

  // Looping over plots
  for(typename map<PlotIndex,PlotType*>::iterator i=this->begin(); i!=this->end(); i++){
    i->second->GetYaxis()->SetRangeUser(min,max);
  }
}

template <class PlotIndex,class PlotType>
void ICPlotCollection<PlotIndex,PlotType>::setYaxisTitle(std::string title){

  // Looping over plots
  for(typename map<PlotIndex,PlotType*>::iterator i=this->begin(); i!=this->end(); i++){
    i->second->GetYaxis()->SetTitle(title.c_str());
  }
}


/********************************************//**
 * Set fill colour for all plots in this container
 * @param attributes map of colours to be applied to each plot 
 ***********************************************/
template <class PlotIndex,class PlotType>
void ICPlotCollection<PlotIndex,PlotType>::setFillColor  (std::map<PlotIndex,int> attributes){

  for(typename std::map<PlotIndex,int>::iterator i=attributes.begin(); i!=attributes.end(); i++){
    if((*this)[i->first])

    (*this)[i->first]->SetFillColor(i->second);
  }
}

/********************************************//**
* Set fill style for all plots in this container
* @param attributes map of styles to be applied to each plot 
***********************************************/
template <class PlotIndex,class PlotType>
void ICPlotCollection<PlotIndex,PlotType>::setFillStyle  (std::map<PlotIndex,int> attributes){

  for(typename std::map<PlotIndex,int>::iterator i=attributes.begin(); i!=attributes.end(); i++){
    (*this)[i->first]->SetFillStyle(i->second);
  }
}

/********************************************//**
* Set marker colour for all plots in this container
* @param attributes map of colours to be applied to each plot markers 
***********************************************/
template <class PlotIndex,class PlotType>
void ICPlotCollection<PlotIndex,PlotType>::setMarkerColor(std::map<PlotIndex,int> attributes){

  for(typename std::map<PlotIndex,int>::iterator i=attributes.begin(); i!=attributes.end(); i++){
    (*this)[i->first]->SetMarkerColor(i->second);
  }
}

/********************************************//**
* Set marker style for all plots in this container
* @param attributes map of styles to be applied to each plot markers 
***********************************************/
template <class PlotIndex,class PlotType>
void ICPlotCollection<PlotIndex,PlotType>::setMarkerStyle(std::map<PlotIndex,int> attributes){

  for(typename std::map<PlotIndex,int>::iterator i=attributes.begin(); i!=attributes.end(); i++){
    (*this)[i->first]->SetMarkerStyle(i->second);
  }
}

/********************************************//**
 * Set marker size for all plots in this container
 * @param attributes map of sizes to be applied to each plot markers 
 ***********************************************/
template <class PlotIndex,class PlotType>
void ICPlotCollection<PlotIndex,PlotType>::setMarkerSize(std::map<PlotIndex,int> attributes){
  
  for(typename std::map<PlotIndex,int>::iterator i=attributes.begin(); i!=attributes.end(); i++){
    (*this)[i->first]->SetMarkerSize(i->second);
  }
}

/********************************************//**
 * Passing legend text and option to be draw when calling draw(...)
 * @param legend map of sizes to be applied to each plot markers
 * @param options options of each entry of the legend 
 ***********************************************/
template <class PlotIndex,class PlotType>
void ICPlotCollection<PlotIndex,PlotType>::setLegend(std::map<PlotIndex,std::string> legend,
                                                     std::map<PlotIndex,std::string> options){

  m_drawLegend    = true;
  m_legendText    = legend;
  m_legendOptions = options;
}

template <class PlotIndex,class PlotType>
void ICPlotCollection<PlotIndex,PlotType>::sumw2(){

  // Looping over plots
  for(typename map<PlotIndex,PlotType*>::iterator i=this->begin(); i!=this->end(); i++){
    i->second->Sumw2();
  }
}

template <class PlotIndex,class PlotType>
void ICPlotCollection<PlotIndex,PlotType>::scale(double factor){

  // Looping over plots
  for(typename map<PlotIndex,PlotType*>::iterator i=this->begin(); i!=this->end(); i++){
    i->second->Scale(factor);
  }
}

#include <iostream>

//___________________________________________________________
template <class PlotIndex,class PlotType>
void ICPlotCollection<PlotIndex,PlotType>::scale(map<PlotIndex,double> weights){
  
  // Looping over plots
  for(typename map<PlotIndex,double>::iterator i=weights.begin(); i!=weights.end(); i++){

    // Protection for when weights have elements not present in this map
    if(this->find(i->first) != this->end()){
      (*this)[i->first]->Scale(i->second);
    }
  }  
}

//___________________________________________________________
template <class PlotIndex,class PlotType>
void ICPlotCollection<PlotIndex,PlotType>::scaleTo1(){

  // Looping over plots
  for(typename map<PlotIndex,PlotType*>::iterator i=this->begin(); i!=this->end(); i++){
    i->second->Scale(1/i->second->Integral());
  }
}

//___________________________________________________________
template <class PlotIndex,class PlotType>
void ICPlotCollection<PlotIndex,PlotType>::rebin(int factor){
  // Looping over plots
  for(typename map<PlotIndex,PlotType*>::iterator i=this->begin(); i!=this->end(); i++){
    i->second->Rebin(factor);
  }
}

//___________________________________________________________
template <class PlotIndex,class PlotType>
PlotType* ICPlotCollection<PlotIndex,PlotType>::getMerged(string name, vector<PlotIndex> selection){
  
  PlotType* out = NULL;  
  
  if(selection.size()==0){return out;}
  
  int counter=0;
  
  for(unsigned i=0; i<selection.size(); i++){
    
    // Protection for when asking to merge elements not present on this map 
    if(this->find(selection[i]) != this->end()){
    
      if(counter==0){
        out = (PlotType*) (*this)[selection[i]]->Clone("name");
        counter++;
      }else{
        out->Add((*this)[selection[i]]);
      }
      
    }else{
      cout << "Could not find plots with identifier: " << selection[i] << endl;
    }
  }
  
  return out;
}

//___________________________________________________________
template <class PlotIndex,class PlotType>
void ICPlotCollection<PlotIndex,PlotType>::draw(TCanvas *canv, std::vector< std::pair<PlotIndex,Option_t*> > attributes){

  double minValue=0;
  double maxValue=0;
  TLegend *l;

  // Loping over all the histograms to be drawn
  for(unsigned i=0; i<attributes.size(); i++){
    PlotType *plot = (*this)[attributes[i].first];

    if(i==0){
      minValue=plot->GetBinContent(plot->GetMinimumBin());
      maxValue=plot->GetBinContent(plot->GetMaximumBin());
    }
    else{
      double tMin = plot->GetBinContent(plot->GetMinimumBin());
      double tMax = plot->GetBinContent(plot->GetMaximumBin());
      if(tMin<minValue){minValue = tMin;}
      if(tMax>maxValue){maxValue = tMax;}
    }
  }

  // Updating the vertical
  setYaxisRangeUser(0,maxValue*1.25);

  // Selecting input canvas for drawing
  canv->cd();

  if(m_drawLegend && m_legendText.size()==m_legendOptions.size()){
   
    l = new TLegend(0.7,0.75,0.9,0.85);
    
    for(unsigned i=0; i<attributes.size(); i++){
      (*this)[attributes[i].first]->Draw(attributes[i].second);
      
      if(m_drawLegend){
        l->AddEntry((*this)[attributes[i].first],m_legendText[attributes[i].first].c_str(),m_legendOptions[attributes[i].first].c_str());
      }
    }
    
    l->Draw();    
  }
}

//The explicit instantiating part
template class ICPlotCollection<int,TH1I>;
template class ICPlotCollection<int,TH1F>;
template class ICPlotCollection<int,TH1D>;
template class ICPlotCollection<int,TH2I>;
template class ICPlotCollection<int,TH2F>;
template class ICPlotCollection<int,TH2D>;

template class ICPlotCollection<string,TH1I>;
template class ICPlotCollection<string,TH1F>;
template class ICPlotCollection<string,TH1D>;
template class ICPlotCollection<string,TH2I>;
template class ICPlotCollection<string,TH2F>;
template class ICPlotCollection<string,TH2D>;