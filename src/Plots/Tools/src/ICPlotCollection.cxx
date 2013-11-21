#include "Plots/Tools/interface/ICPlotCollection.h"

#include "TLegend.h"

using namespace std;

template <class PlotIndex,class PlotType>
ICPlotCollection<PlotIndex,PlotType>::ICPlotCollection(){

  drawLegend_=false;

}

template <class PlotIndex,class PlotType>
void ICPlotCollection<PlotIndex,PlotType>::SetXaxisRangeUser(double min,double max){

  // Looping over plots
  for(typename map<PlotIndex,PlotType*>::iterator i=this->begin(); i!=this->end(); i++){
    i->second->GetXaxis()->SetRangeUser(min,max);
  }
}

template <class PlotIndex,class PlotType>
void ICPlotCollection<PlotIndex,PlotType>::SetXaxisTitle(std::string title){

  // Looping over plots
  for(typename map<PlotIndex,PlotType*>::iterator i=this->begin(); i!=this->end(); i++){
    i->second->GetXaxis()->SetTitle(title.c_str());
  }
}

template <class PlotIndex,class PlotType>
void ICPlotCollection<PlotIndex,PlotType>::SetYaxisRangeUser(double min,double max){

  // Looping over plots
  for(typename map<PlotIndex,PlotType*>::iterator i=this->begin(); i!=this->end(); i++){
    i->second->GetYaxis()->SetRangeUser(min,max);
  }
}

template <class PlotIndex,class PlotType>
void ICPlotCollection<PlotIndex,PlotType>::SetYaxisTitle(std::string title){

  // Looping over plots
  for(typename map<PlotIndex,PlotType*>::iterator i=this->begin(); i!=this->end(); i++){
    i->second->GetYaxis()->SetTitle(title.c_str());
  }
}

template <class PlotIndex,class PlotType>
void ICPlotCollection<PlotIndex,PlotType>::SetFillColor  (std::map<PlotIndex,int> attributes){

  for(typename std::map<PlotIndex,int>::iterator i=attributes.begin(); i!=attributes.end(); i++){
    if((*this)[i->first])

    (*this)[i->first]->SetFillColor(i->second);
  }
}

template <class PlotIndex,class PlotType>
void ICPlotCollection<PlotIndex,PlotType>::SetFillStyle  (std::map<PlotIndex,int> attributes){

  for(typename std::map<PlotIndex,int>::iterator i=attributes.begin(); i!=attributes.end(); i++){
    (*this)[i->first]->SetFillStyle(i->second);
  }
}

template <class PlotIndex,class PlotType>
void ICPlotCollection<PlotIndex,PlotType>::SetMarkerColor(std::map<PlotIndex,int> attributes){

  for(typename std::map<PlotIndex,int>::iterator i=attributes.begin(); i!=attributes.end(); i++){
    (*this)[i->first]->SetMarkerColor(i->second);
  }
}

template <class PlotIndex,class PlotType>
void ICPlotCollection<PlotIndex,PlotType>::SetMarkerStyle(std::map<PlotIndex,int> attributes){

  for(typename std::map<PlotIndex,int>::iterator i=attributes.begin(); i!=attributes.end(); i++){
    (*this)[i->first]->SetMarkerStyle(i->second);
  }
}

template <class PlotIndex,class PlotType>
void ICPlotCollection<PlotIndex,PlotType>::SetLegend(std::map<PlotIndex,std::string> legend,
                                                     std::map<PlotIndex,std::string> legendAttributes){

  drawLegend_       = true;
  legend_           = legend;
  legendAttributes_ = legendAttributes;
}

template <class PlotIndex,class PlotType>
void ICPlotCollection<PlotIndex,PlotType>::Sumw2(){

  // Looping over plots
  for(typename map<PlotIndex,PlotType*>::iterator i=this->begin(); i!=this->end(); i++){
    i->second->Sumw2();
  }
}

template <class PlotIndex,class PlotType>
void ICPlotCollection<PlotIndex,PlotType>::Scale(double factor){

  // Looping over plots
  for(typename map<PlotIndex,PlotType*>::iterator i=this->begin(); i!=this->end(); i++){
    i->second->Scale(factor);
  }
}

//___________________________________________________________
template <class PlotIndex,class PlotType>
void ICPlotCollection<PlotIndex,PlotType>::ScaleTo1(){

  // Looping over plots
  for(typename map<PlotIndex,PlotType*>::iterator i=this->begin(); i!=this->end(); i++){
    i->second->Scale(1/i->second->Integral());
  }
}

//___________________________________________________________
template <class PlotIndex,class PlotType>
void ICPlotCollection<PlotIndex,PlotType>::Rebin(int factor){
  // Looping over plots
  for(typename map<PlotIndex,PlotType*>::iterator i=this->begin(); i!=this->end(); i++){
    i->second->Rebin(factor);
  }
}

//___________________________________________________________
template <class PlotIndex,class PlotType>
void ICPlotCollection<PlotIndex,PlotType>::Draw(TCanvas *canv, std::vector< std::pair<PlotIndex,Option_t*> > attributes){

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
  SetYaxisRangeUser(0,maxValue*1.25);

  // Selecting input canvas for drawing
  canv->cd();

  if(drawLegend_ && legend_.size()==legendAttributes_.size()){
    l = new TLegend(0.7,0.75,0.9,0.85);
  }else{
    drawLegend_=false;
  }

  for(unsigned i=0; i<attributes.size(); i++){
    (*this)[attributes[i].first]->Draw(attributes[i].second);

    if(drawLegend_){
      l->AddEntry((*this)[attributes[i].first],legend_[attributes[i].first].c_str(),legendAttributes_[attributes[i].first].c_str());
    }
  }
  if(drawLegend_){l->Draw();}
}
