#ifndef PLOTS_TOOLS_PLOTFWD
#define PLOTS_TOOLS_PLOTFWD

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

typedef rat::PlotCollection<int,TH1I> rat::MapInt_ICH1I;
typedef rat::PlotCollection<int,TH1F> rat::MapInt_ICH1F;
typedef rat::PlotCollection<int,TH1D> rat::MapInt_ICH1D;
typedef rat::PlotCollection<int,TH2F> rat::MapInt_ICH2F;
typedef rat::PlotCollection<int,TH2D> rat::MapInt_ICH2D;

typedef rat::PlotCollection<std::string,TH1I> rat::MapString_ICH1I;
typedef rat::PlotCollection<std::string,TH1F> rat::MapString_ICH1F;
typedef rat::PlotCollection<std::string,TH1D> rat::MapString_ICH1D;
typedef rat::PlotCollection<std::string,TH2F> rat::MapString_ICH2F;
typedef rat::PlotCollection<std::string,TH2D> rat::MapString_ICH2D;

#endif