#include <vector>
#include <map>
#include <utility>
#include <string>
#include "DataFormats/ICHiggsTauTau/interface/Candidate.h"
#include "DataFormats/ICHiggsTauTau/interface/GenParticle.h"
#include "DataFormats/ICHiggsTauTau/interface/Jet.h"
#include "DataFormats/ICHiggsTauTau/interface/CaloJet.h"
#include "DataFormats/ICHiggsTauTau/interface/PFJet.h"
#include "DataFormats/ICHiggsTauTau/interface/JPTJet.h"
#include "DataFormats/ICHiggsTauTau/interface/Track.h"
#include "DataFormats/ICHiggsTauTau/interface/LightTrack.h"
#include "DataFormats/ICHiggsTauTau/interface/GenJet.h"
#include "DataFormats/ICHiggsTauTau/interface/Vertex.h"
#include "DataFormats/ICHiggsTauTau/interface/Electron.h"
#include "DataFormats/ICHiggsTauTau/interface/Photon.h"
#include "DataFormats/ICHiggsTauTau/interface/Muon.h"
#include "DataFormats/ICHiggsTauTau/interface/EventInfo.h"
#include "DataFormats/ICHiggsTauTau/interface/PileupInfo.h"
#include "DataFormats/ICHiggsTauTau/interface/TriggerPath.h"
#include "DataFormats/ICHiggsTauTau/interface/Met.h"
#include "DataFormats/ICHiggsTauTau/interface/Tau.h"
#include "DataFormats/ICHiggsTauTau/interface/SuperCluster.h"
#include "DataFormats/ICHiggsTauTau/interface/TriggerObject.h"
#include "DataFormats/ICHiggsTauTau/interface/TH2DAsymErr.h"
#include "DataFormats/Common/interface/Wrapper.h"

namespace { struct dictionary {
  ic::Candidate dummy1;
  std::vector<ic::Candidate> dummy2;
  ic::Jet dummy3;
  std::vector<ic::Jet> dummy4;
  std::map<size_t, float> dummy5;
  ic::CaloJet dummy6;
  std::vector<ic::CaloJet> dummy7;
  ic::GenParticle dummy8;
  std::vector<ic::GenParticle> dummy9;
  ic::PFJet dummy10;
  std::vector<ic::PFJet> dummy11;
  ic::JPTJet dummy12;
  std::vector<ic::JPTJet> dummy13;
  ic::Track dummy14;
  std::vector<ic::Track> dummy15;
  ic::GenJet dummy16;
  std::vector<ic::GenJet> dummy17;
  ic::Vertex dummy18;
  std::vector<ic::Vertex> dummy19;
  std::pair<unsigned long, float> dummy20;
  std::vector< std::pair<unsigned long, float> > dummy21;
  ic::Electron dummy22;
  std::vector<ic::Electron> dummy23;
  ic::Muon dummy24;
  std::vector<ic::Muon> dummy25;
  std::pair<std::string, double> dummy26;
  std::vector< std::pair<std::string, double> > dummy27;
  ic::EventInfo dummy28;
  ic::PileupInfo dummy30;
  std::vector<ic::PileupInfo> dummy31;
  ic::TriggerPath dummy32;
  std::vector<ic::TriggerPath> dummy33;
  ic::Met dummy34;
  ic::LightTrack dummy35;
  std::vector<ic::LightTrack> dummy36;
  ic::Tau dummy37;
  std::vector<ic::Tau> dummy38;
  ic::SuperCluster dummy39;
  std::vector<ic::SuperCluster> dummy40;
  ic::TriggerObject dummy41;
  std::vector<ic::TriggerObject> dummy42;
  std::vector<ic::Met> dummy43;
  std::vector<unsigned long> dummy44;
  edm::Wrapper<std::vector<unsigned long> > dummy45;
  mithep::TH2DAsymErr dummy46;
  ic::Photon dummy47;
  std::vector<ic::Photon> dummy48;
};
}

