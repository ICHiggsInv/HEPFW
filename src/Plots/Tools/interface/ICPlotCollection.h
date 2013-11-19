#ifndef ICTOOLS_PLOTS_ICPLOTCOLLECTION
#define ICTOOLS_PLOTS_ICPLOTCOLLECTION

#include "TCanvas.h"

#include <map>

template <class PlotIndex,class PlotType>
class ICPlotCollection : public std::map<PlotIndex,PlotType*> {

public:

  ICPlotCollection();

  void SetXaxisRangeUser(double min,double max);
  void SetXaxisTitle(std::string title);

  void SetYaxisRangeUser(double min,double max);
  void SetYaxisTitle(std::string title);

  void SetFillColor  (std::map<PlotIndex,int> attributes);
  void SetFillStyle  (std::map<PlotIndex,int> attributes);
  void SetMarkerColor(std::map<PlotIndex,int> attributes);
  void SetMarkerStyle(std::map<PlotIndex,int> attributes);
  void SetLegend(std::map<PlotIndex,std::string> legend,std::map<PlotIndex,std::string> legendAttributes);
  
  void Sumw2();
  void Scale(double factor);
  void ScaleTo1();
  void Rebin(int factor);

  void Draw(TCanvas *canv,std::vector< std::pair<PlotIndex,Option_t*> > attributes);

private:

  bool drawLegend_;
  std::map<PlotIndex,std::string> legend_;
  std::map<PlotIndex,std::string> legendAttributes_;
  
};

#endif