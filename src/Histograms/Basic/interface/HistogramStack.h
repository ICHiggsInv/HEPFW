#ifndef HISTOGRAMS_DATAFORMATS_HISTOGRAMSTACK
#define HISTOGRAMS_DATAFORMATS_HISTOGRAMSTACK

namespace rat{
  
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