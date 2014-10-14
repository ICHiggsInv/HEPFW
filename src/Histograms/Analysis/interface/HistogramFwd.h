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

typedef hepfw::PlotCollection<int,TH1I> hepfw::MapInt_ICH1I;
typedef hepfw::PlotCollection<int,TH1F> hepfw::MapInt_ICH1F;
typedef hepfw::PlotCollection<int,TH1D> hepfw::MapInt_ICH1D;
typedef hepfw::PlotCollection<int,TH2F> hepfw::MapInt_ICH2F;
typedef hepfw::PlotCollection<int,TH2D> hepfw::MapInt_ICH2D;

typedef hepfw::PlotCollection<std::string,TH1I> hepfw::MapString_ICH1I;
typedef hepfw::PlotCollection<std::string,TH1F> hepfw::MapString_ICH1F;
typedef hepfw::PlotCollection<std::string,TH1D> hepfw::MapString_ICH1D;
typedef hepfw::PlotCollection<std::string,TH2F> hepfw::MapString_ICH2F;
typedef hepfw::PlotCollection<std::string,TH2D> hepfw::MapString_ICH2D;

#endif