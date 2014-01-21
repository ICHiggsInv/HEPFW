#ifndef PLOTS_TOOLS_ICPLOTFWD
#define PLOTS_TOOLS_ICPLOTFWD

// IC Framework included
#include "Plots/Tools/interface/ICPlotCollection.h"

// ROOT Includes
#include "TH1F.h"
#include "TH1D.h"
#include "TH2F.h"
#include "TH2D.h"

// C++ Included
#include <map>
#include <string>
#include <utility>

typedef ICPlotCollection<int,TH1I> MapInt_ICH1I;
typedef ICPlotCollection<int,TH1F> MapInt_ICH1F;
typedef ICPlotCollection<int,TH1D> MapInt_ICH1D;
typedef ICPlotCollection<int,TH2F> MapInt_ICH2F;
typedef ICPlotCollection<int,TH2D> MapInt_ICH2D;

typedef ICPlotCollection<std::string,TH1I> MapString_ICH1I;
typedef ICPlotCollection<std::string,TH1F> MapString_ICH1F;
typedef ICPlotCollection<std::string,TH1D> MapString_ICH1D;
typedef ICPlotCollection<std::string,TH2F> MapString_ICH2F;
typedef ICPlotCollection<std::string,TH2D> MapString_ICH2D;

#endif