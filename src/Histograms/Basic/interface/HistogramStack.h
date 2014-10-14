#ifndef HISTOGRAMS_DATAFORMATS_HISTOGRAMSTACK
#define HISTOGRAMS_DATAFORMATS_HISTOGRAMSTACK

namespace hepfw{
  
  /***********************************************/
  /** \brief HistogramStack
   * 
   * HistogramStack
   ***********************************************/
  class HistogramStack : public THStack {
  public:
    
    HistogramStack();
    ~HistogramStack();
    
  };
  
}
 
#endif