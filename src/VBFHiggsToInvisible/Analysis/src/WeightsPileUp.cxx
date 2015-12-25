#include "VBFHiggsToInvisible/Analysis/interface/WeightsPileUp.h"

// ICHiggsTauTau
#include "DataFormats/ICHiggsTauTau/interface/EventInfo.h"
#include "DataFormats/ICHiggsTauTau/interface/PileupInfo.h"

using namespace std;

hepfw::WeightsPileUp::WeightsPileUp(){
  m_name = "";
}

hepfw::WeightsPileUp::WeightsPileUp(std::string name){
  m_name = name;
}

void hepfw::WeightsPileUp::beginJob(hepfw::JobSetup &job){
  
}

hepfw::WeightsPileUp::WeightsPileUp(std::string name,hepfw::ParameterSet &pset,hepfw::Dataset &dataset){
  m_name = name;
  
  string datasetName = dataset.getName();
  
  string mc_pu_file   = "/vols/cms02/jca10/work/slc6/dev01/cc/HEPFW_v2/src/VBFHiggsToInvisible/Analysis/data/Weights/pileup/MC_Summer12_PU_S10-600bins.root";           // summer12_53X
  string data_pu_file = "/vols/cms02/jca10/work/slc6/dev01/cc/HEPFW_v2/src/VBFHiggsToInvisible/Analysis/data/Weights/pileup/Data_Pileup_2012_ReRecoPixel-600bins.root"; // era::data_2012_rereco
  
  TFile *filePUData = new TFile(data_pu_file.c_str());
  TFile *filePUMC   = new TFile(mc_pu_file.c_str());
  
  m_hPUData = (TH1D*) filePUData->Get("pileup");
  m_hPUMC   = (TH1D*) filePUMC  ->Get("pileup");
  
  unsigned nbins_data = m_hPUData->GetNbinsX();
  unsigned nbins_mc   = m_hPUMC->GetNbinsX();
  double   min_data   = m_hPUData->GetBinLowEdge(1);
  double   min_mc     = m_hPUMC->GetBinLowEdge(1);
  double   max_data   = m_hPUData->GetBinLowEdge(nbins_data) + m_hPUData->GetBinWidth(nbins_data);
  double   max_mc     = m_hPUMC->GetBinLowEdge(nbins_mc) + m_hPUMC->GetBinWidth(nbins_mc);
  unsigned nbins      = nbins_data > nbins_mc ? nbins_data : nbins_mc;
  
  cout << "[hepfw::WeightsPileUp] Dataset name             = " << datasetName << endl;
  
  if (m_hPUData && m_hPUMC) {
    std::cout << "[hepfw::WeightsPileUp] Input data histogram has " << nbins_data << " bins in the range [" << min_data << "," << max_data << "]" << std::endl;
    std::cout << "[hepfw::WeightsPileUp] Input MC histogram has " << nbins_mc << " bins in the range [" << min_mc << "," << max_mc << "]" << std::endl;
    std::cout << "[hepfw::WeightsPileUp] Weights calculated for " << nbins << " bins" << std::endl;
  } else {
    std::cout << "[hepfw::WeightsPileUp] Invalid histogram!" << std::endl;
  }
  m_hPUData->Scale(1./m_hPUData->Integral());
  m_hPUMC->Scale(1./m_hPUMC->Integral());
  m_weights = (TH1D*)m_hPUData->Clone();
  m_weights->Divide(m_hPUMC);
}

hepfw::WeightsPileUp::~WeightsPileUp(){
  
}

void hepfw::WeightsPileUp::produce(hepfw::Event &event){
  
  // From Patrick defaults
  bool use_sampled_interactions_ = false;
//   ic::ElectronCollection *inElectrons = event.getByName<ic::ElectronCollection>(m_inputLabel);
  vector<ic::PileupInfo> *puInfo    = event.getByName< vector<ic::PileupInfo> >("pileupInfo");
  
  float true_int = -1;
  for (unsigned i = 0; i < puInfo->size(); ++i) {
    if ((*puInfo)[i].bunch_crossing() == 0) {
      true_int = use_sampled_interactions_ ?
      (*puInfo)[i].num_interactions() : (*puInfo)[i].true_num_interactions();
    }
  }
  if (true_int < 0) {
    std::cout << "Warning: In-time true_num_interactions not found!" << std::endl;
    return;
  }

  int found_bin = m_weights->FindBin(true_int);
  double weight = 1.0;
  if (found_bin >= 1 && found_bin <= m_weights->GetNbinsX()) {
    weight = m_weights->GetBinContent(found_bin);
  }
  
  event.addWeight("weightPu",weight);
}

