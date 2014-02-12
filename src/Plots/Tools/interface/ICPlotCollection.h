#ifndef PLOTS_TOOLS_ICPLOTCOLLECTION
#define PLOTS_TOOLS_ICPLOTCOLLECTION

#include "TCanvas.h"
#include "TFile.h"

#include <map>

template <class PlotIndex,class PlotType>
class ICPlotCollection : public std::map<PlotIndex,PlotType*> {

public:

  ICPlotCollection();
  ICPlotCollection(std::map<PlotIndex,TFile*> samples,std::string path);

  // X-Axis  
  void setXaxisRangeUser(double min,double max);
  void setXaxisTitle(std::string title);

  // Y-Axis
  void setYaxisRangeUser(double min,double max);
  void setYaxisTitle(std::string title);
  
  // Fill
  void setFillColor  (std::map<PlotIndex,int> attributes);
  void setFillStyle  (std::map<PlotIndex,int> attributes);

  // Marker
  void setMarkerColor(std::map<PlotIndex,int> attributes);
  void setMarkerStyle(std::map<PlotIndex,int> attributes);
  void setMarkerSize(std::map<PlotIndex,int> attributes);  

  void setLegend     (std::map<PlotIndex,std::string> legend,std::map<PlotIndex,std::string> legendAttributes);
  
  void scale   (double factor);
  void scale   (std::map<PlotIndex,double> weights);
  void scaleTo1();
  void sumw2();
  void rebin(int factor);

  PlotType* getMerged(std::string name,std::vector<PlotIndex> selection);
  
  void draw(TCanvas *canv,std::vector< std::pair<PlotIndex,Option_t*> > attributes);

private:

  bool m_drawLegend;
  std::map<PlotIndex,std::string> m_legendText;
  std::map<PlotIndex,std::string> m_legendOptions;
  
};

#endif