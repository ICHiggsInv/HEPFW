#ifndef HISTOGRAM_ANALYSIS_PLOTCOLLECTION
#define HISTOGRAM_ANALYSIS_PLOTCOLLECTION

#include "TCanvas.h"
#include "TFile.h"

#include "TLegend.h"
#include "TH1F.h"
#include "TH1D.h"
#include "TH2F.h"
#include "TH2D.h"

#include <string>
#include <stdio.h>
#include <iostream>
#include <map>

namespace hepfw{
  
  /***********************************************/
  /** \brief HistogramCollection 
   * 
   * HistogramCollection
   ***********************************************/
  template <class PlotIndex,class PlotType>
  class HistogramCollection : public std::map<PlotIndex,PlotType*>{
  public:
    
    /********************************************//**
    * Defaults constructor for this class
    ***********************************************/
    HistogramCollection() : std::map<PlotIndex,PlotType*>(){
      m_drawLegend=false;
    }
    
    /********************************************//**
    * Constructor that will take a map of files and a path to a plot,
    * open all files and retrive the plot stored at that path. 
    * @param samples minimum value to be visible on this axis 
    * @param path    maximum value to be visible on this axis
    ***********************************************/
    HistogramCollection(std::map<PlotIndex,TFile*> samples,std::string path) : std::map<PlotIndex,PlotType*>(){
      m_drawLegend=false;
      
      for(typename std::map<PlotIndex,TFile*>::iterator i=samples.begin(); i!=samples.end(); i++){

        TFile* file = i->second;
        
        if( file->IsZombie()){
          std::cout << "WARNING: File with handle '" << i->first << "' is in zombie state!" << std::endl;
          continue;
        }
        if(!file->IsOpen()){
          std::cout << "WARNING: File with handle '" << i->first << "' is not open!" << std::endl;
          continue;
        }
        
        (*this)[i->first] = (PlotType*) file->Get(path.c_str());
      } 
    }
    
    /********************************************//**
    * Set x-axis user defined range (zooms plot to new range) from min to max
    * @param min minimum value to be visible on this axis 
    * @param max maximum value to be visible on this axis 
    ***********************************************/
    void setXaxisRangeUser(double min,double max){
      
      // Looping over plots
      for(typename std::map<PlotIndex,PlotType*>::iterator i=this->begin(); i!=this->end(); i++){
        i->second->GetXaxis()->SetRangeUser(min,max);
      }
    }
    
    /********************************************//**
    * Set y-axis title (axis caption) for all plots in this container
    * @param title title to be applied to x-axis of all plots
    ***********************************************/
    void setXaxisTitle(std::string title){
      
      // Looping over plots
      for(typename std::map<PlotIndex,PlotType*>::iterator i=this->begin(); i!=this->end(); i++){
        i->second->GetXaxis()->SetTitle(title.c_str());
      }
    }
    
    /********************************************//**
    * Set y-axis user defined range (zooms plot to new range) from min to max
    * @param min minimum value to be visible on this axis 
    * @param max maximum value to be visible on this axis 
    ***********************************************/
    void setYaxisRangeUser(double min,double max){
      
      // Looping over plots
      for(typename std::map<PlotIndex,PlotType*>::iterator i=this->begin(); i!=this->end(); i++){
        i->second->GetYaxis()->SetRangeUser(min,max);
      }
    }
    
    /********************************************//**
    * Set y-axis title (axis caption) for all plots in this container
    * @param title title to be applied to y-axis of all plots
    ***********************************************/
    void setYaxisTitle(std::string title){
      
      // Looping over plots
      for(typename std::map<PlotIndex,PlotType*>::iterator i=this->begin(); i!=this->end(); i++){
        i->second->GetYaxis()->SetTitle(title.c_str());
      }
    }

    /********************************************//**
    * Set line colour for all plots in this container
    * @param attributes map of colours to be applied to each plot 
    ***********************************************/
    void setLineColor(std::map<PlotIndex,int> attributes){
      
      for(typename std::map<PlotIndex,int>::iterator i=attributes.begin(); i!=attributes.end(); i++){
        if((*this)[i->first])
          
          (*this)[i->first]->SetLineColor(i->second);
      }
    }
    
    /********************************************//**
    * Set fill colour for all plots in this container
    * @param attributes map of colours to be applied to each plot 
    ***********************************************/
    void setFillColor(std::map<PlotIndex,int> attributes){
      
      for(typename std::map<PlotIndex,int>::iterator i=attributes.begin(); i!=attributes.end(); i++){
        if((*this)[i->first])
          
          (*this)[i->first]->SetFillColor(i->second);
      }
    }
    
    /********************************************//**
    * Set fill style for all plots in this container
    * @param attributes map of styles to be applied to each plot 
    ***********************************************/
    void setFillStyle  (std::map<PlotIndex,int> attributes){
      
      for(typename std::map<PlotIndex,int>::iterator i=attributes.begin(); i!=attributes.end(); i++){
        (*this)[i->first]->SetFillStyle(i->second);
      }
    }
    
    /********************************************//**
    * Set marker colour for all plots in this container
    * @param attributes map of colours to be applied to each plot markers 
    ***********************************************/
    void setMarkerColor(std::map<PlotIndex,int> attributes){
      
      for(typename std::map<PlotIndex,int>::iterator i=attributes.begin(); i!=attributes.end(); i++){
        (*this)[i->first]->SetMarkerColor(i->second);
      }
    }
    
    /********************************************//**
    * Set marker style for all plots in this container
    * @param attributes map of styles to be applied to each plot markers 
    ***********************************************/
    void setMarkerStyle(std::map<PlotIndex,int> attributes){
      
      for(typename std::map<PlotIndex,int>::iterator i=attributes.begin(); i!=attributes.end(); i++){
        (*this)[i->first]->SetMarkerStyle(i->second);
      }
    }

    /********************************************//**
    * Set marker size for all plots in this container
    * @param attributes map of sizes to be applied to each plot markers 
    ***********************************************/
    void setMarkerSize(std::map<PlotIndex,int> attributes){
      
      for(typename std::map<PlotIndex,int>::iterator i=attributes.begin(); i!=attributes.end(); i++){
        (*this)[i->first]->SetMarkerSize(i->second);
      }
    }
    
    /********************************************//**
    * Passing legend text and option to be draw when calling draw(...)
    * @param legend map of sizes to be applied to each plot markers
    * @param options options of each entry of the legend 
    ***********************************************/
    void setLegend(std::map<PlotIndex,std::string> legend,std::map<PlotIndex,std::string> legendAttributes){

      m_drawLegend    = true;
      m_legendText    = legend;
      m_legendOptions = legendAttributes;
    }
    
    /********************************************//**
    * Scale all plots by a factor
    * @param factor factor to multiply all plots
    ***********************************************/
    void scale(double factor){
      
      // Looping over plots
      for(typename std::map<PlotIndex,PlotType*>::iterator i=this->begin(); i!=this->end(); i++){
        i->second->Scale(factor);
      }
    }
    
    /********************************************//**
    * Scale plots according to an input map of weights
    * @param weights map of weights indexed by keys to indicate to which plot they should be applied
    ***********************************************/
    void scale(std::map<PlotIndex,double> weights){
      
      // Looping over plots
      for(typename std::map<PlotIndex,double>::iterator i=weights.begin(); i!=weights.end(); i++){
        
        // Protection for when weights have elements not present in this map
        if(this->find(i->first) != this->end()){
          (*this)[i->first]->Scale(i->second);
        }
      }  
    }
    
    /********************************************//**
    * Scale all contained plots to one by using plots built in Integral() function.
    * 
    * NOTE: The integral does take into account under and overflow bins.  
    ***********************************************/
    void scaleTo1(){
      
      this->setYaxisTitle("Scaled to 1");
      
      // Looping over plots
      for(typename std::map<PlotIndex,PlotType*>::iterator i=this->begin(); i!=this->end(); i++){
        double fullIntegral = i->second->Integral(0,i->second->GetNbinsX()+1);
        i->second->Scale(1/fullIntegral);
      }
    }
    
    /********************************************//**
    * Call Sumw2() method on all plots
    ***********************************************/
    void sumw2(){
      
      // Looping over plots
      for(typename std::map<PlotIndex,PlotType*>::iterator i=this->begin(); i!=this->end(); i++){
        i->second->Sumw2();
      }
    }
    
    /********************************************//**
    * Rebin all contained plots according to an input map of factors
    * @param factor factor to be used to rebin plots
    ***********************************************/
    void rebin(int factor){
      
      // Looping over plots
      for(typename std::map<PlotIndex,PlotType*>::iterator i=this->begin(); i!=this->end(); i++){
        i->second->Rebin(factor);
      }
    }
    
    /********************************************//**
    * Create and return new plots by adding a set of contained plots
    * @param name name for the output plots
    * @param selection vector with the identifiers of the plots to be added and returned 
    * @return plot resulting from adding all plots found on this contained matching the identifiers on the selection
    ***********************************************/
    PlotType* getMerged(std::string name,std::vector<PlotIndex> selection){
      
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
          std::cout << "WARNING: Could not find plots with identifier: " << selection[i] << std::endl;
        }
      }
      
      return out;
    }
    
    /********************************************//**
    * Draw a subset of plots in this contained into an input TCanvas.
    * 
    * This method will take in a TCanvas pointer and draw in it histograms from
    * this container following the order and with the attributes present in the
    * input variable histograms.
    * 
    * Vertical axis user range will automatically be set to 125% of the maximum
    * value of any selected plot. This is to avoid plots being plotted out of bounds.
    * 
    * If defined legends will be draw on the top right corner.
    * 
    * @param canv input TCanvas where plots will be draw
    * @param attributes vector of pairs of (index,draw histograms) to be used on drawing.    
    * @return plot resulting from adding all plots found on this contained matching the identifiers on the selection
    ***********************************************/
    void draw(TCanvas *canv,std::vector< std::pair<PlotIndex,Option_t*> > attributes){
      
      
      double minValue=0;
      double maxValue=0;
      
      TLegend *l = 0;
      if(m_drawLegend){
        l = new TLegend(0.7,0.75,0.9,0.85);
      }
      
      // Selecting input canvas for drawing
      canv->cd();
      
      // Loping over all the histograms to be drawn
      for(unsigned i=0; i<attributes.size(); i++){
        
        std::pair<PlotIndex,Option_t*> *opt = &(attributes[i]);
        
        // Protection for when 'histograms' have elements not present in this map
        if(this->find(opt->first) != this->end()){
          
          PlotType *plot = (*this)[opt->first];
          
          // Determinining maximum of the plot
          if(i==0){
            minValue = plot->GetBinContent(plot->GetMinimumBin());
            maxValue = plot->GetBinContent(plot->GetMaximumBin());
          }
          else{
            double tMin = plot->GetBinContent(plot->GetMinimumBin());
            double tMax = plot->GetBinContent(plot->GetMaximumBin());
            if(tMin<minValue){minValue = tMin;}
            if(tMax>maxValue){maxValue = tMax;}
          }
          
          // Drawing plot
          plot->Draw(opt->second);
          
          // Adding entry to legend
          // TODO: Add check that legend exists
          if(m_drawLegend){
            l->AddEntry(plot,m_legendText[opt->first].c_str(),m_legendOptions[opt->first].c_str());
          }
        }
        else{
          std::cout << "ERROR: Attempt to draw Plot with non existent identifier: " << opt->first << std::endl;
        }
      }
      
      // Updating the vertical
//       setYaxisRangeUser(0,maxValue*1.25);
      
      if(m_drawLegend){l->Draw();}  
    }
    
    /********************************************//**
    * Rebin all contained plots according to an input map of factors
    * @param factor factor to be used to rebin plots
    ***********************************************/
    std::string toString(){
      
      std::string out = "";
      
      // Looping over plots
      for(typename std::map<PlotIndex,PlotType*>::iterator i=this->begin(); i!=this->end(); i++){
        out += "Element=";
        out += i->first;
        out += " title=";
        out += i->second->GetTitle();
        out += "\n";
      }
      
      return out;
    }
    
    
  private:
    
    bool m_drawLegend;
    std::map<PlotIndex,std::string> m_legendText;
    std::map<PlotIndex,std::string> m_legendOptions;
    
  };    
}

#endif