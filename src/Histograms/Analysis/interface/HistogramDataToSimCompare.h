#ifndef HISTOGRAMS_ANALYSIS_HISTOGRAMDATATOSIMCOMPARE
#define HISTOGRAMS_ANALYSIS_HISTOGRAMDATATOSIMCOMPARE

// #include "Histograms/DataFormats/interface/Histogram1D.h"
// #include "Histograms/DataFormats/interface/HistogramFwd.h"

#include "TCanvas.h"
#include "TH1D.h"
#include "TLegend.h"
#include "THStack.h"

#include <map>
#include <string>

namespace hepfw{
  
  /***********************************************/
  /** \brief Data to simulation compare of histograms
   * 
   * This class allows comparison between data and simulation (typically a stack) of
   * histograms.
   ***********************************************/ 
  class HistogramDataToSimCompare {  
  public:

    HistogramDataToSimCompare();    
    HistogramDataToSimCompare(std::string name);
    ~HistogramDataToSimCompare();
    
    void addSimHistogram (TH1D *histogram, std::string name, bool passOwnership=false);
    void addDataHistogram(TH1D *histogram, bool passOwnership=false);
    
    void setAutoRangeYaxis        (bool value=true,bool forceZero=false);
    void setAutoOrderSimHistograms(bool value=true);
    
    void setLogy(bool value=true);    
    void setBlindData(double low,double high);
    
    void setDoRatioPlot(bool value=true);
    
    std::pair<double,double> getAutoRangeYaxis();
    
    TCanvas* draw();

  private:
    
    void                     init();
    void                     doBlindData();
    
  private:
    
    bool m_autoRangeYaxis;
    bool m_autoRangeYaxisforceZero;
    bool m_autoOrderSimHistograms;
    bool m_doRatioPlot;
    bool m_doLogy;
    bool m_doBlindData;
    
    double m_BlindDataLow;
    double m_BlindDataHigh;
    
    std::string m_name;
    
    TH1D    *m_data; 
    THStack *m_simStack;
    TLegend *m_legend;
    
    std::vector<TH1D*> m_histOwned;
    
    std::map<std::string,TH1D*> m_histograms; 
    
    
  };
  
};

#endif 
