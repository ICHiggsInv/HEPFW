#include "VBFHiggsToInvisible/Analysis/interface/WeightsLepton.h"

// ICHiggsTauTau
#include "DataFormats/ICHiggsTauTau/interface/EventInfo.h"
#include "DataFormats/ICHiggsTauTau/interface/PileupInfo.h"
#include "DataFormats/ICHiggsTauTau/interface/Candidate.h"
#include "DataFormats/ICHiggsTauTau/interface/GenParticle.h"

// ICHiggsTauTau
#include "DataFormats/ICHiggsTauTau/interface/PFJet.h"
#include "DataFormats/ICHiggsTauTau/interface/Met.h"

#include "iostream"
#include "fstream"
#include "sstream"

using namespace std;

hepfw::WeightsLepton::WeightsLepton(){
  m_name = "";
  m_do_idiso_tight_weights = false;
  m_do_idiso_veto_weights  = false;
}

hepfw::WeightsLepton::WeightsLepton(std::string name){
  m_name = name;
  m_do_idiso_tight_weights = false;
  m_do_idiso_veto_weights  = false;
}

void hepfw::WeightsLepton::beginJob(hepfw::JobSetup &job){
  
}

hepfw::WeightsLepton::WeightsLepton(std::string name,hepfw::ParameterSet &pset,hepfw::Dataset &dataset){
  m_name = name;
  m_do_idiso_tight_weights = false;
  m_do_idiso_veto_weights  = false;
  
  m_datasetName = dataset.getName();
  
  m_do_idiso_tight_weights = pset.getParameter<bool>("do_idiso_tight_weights");
  m_do_idiso_veto_weights  = pset.getParameter<bool>("do_idiso_veto_weights");
  
  eTight_idisoSF_.push_back(0.827);
  eTight_idisoSF_.push_back(0.924);
  eTight_idisoSF_.push_back(0.96 );
  eTight_idisoSF_.push_back(0.978);
  eTight_idisoSF_.push_back(0.981);
  eTight_idisoSF_.push_back(0.982);
  eTight_idisoSF_.push_back(0.948);
  eTight_idisoSF_.push_back(0.932);
  eTight_idisoSF_.push_back(0.936);
  eTight_idisoSF_.push_back(0.958);
  eTight_idisoSF_.push_back(0.969);
  eTight_idisoSF_.push_back(0.969);
  eTight_idisoSF_.push_back(1.073);
  eTight_idisoSF_.push_back(0.808);
  eTight_idisoSF_.push_back(0.933);
  eTight_idisoSF_.push_back(0.907);
  eTight_idisoSF_.push_back(0.904);
  eTight_idisoSF_.push_back(0.926);
  eTight_idisoSF_.push_back(0.854);
  eTight_idisoSF_.push_back(0.853);
  eTight_idisoSF_.push_back(0.879);
  eTight_idisoSF_.push_back(0.909);
  eTight_idisoSF_.push_back(0.942);
  eTight_idisoSF_.push_back(0.957);
  eTight_idisoSF_.push_back(1.007);
  eTight_idisoSF_.push_back(0.903);
  eTight_idisoSF_.push_back(0.974);
  eTight_idisoSF_.push_back(0.987);
  eTight_idisoSF_.push_back(0.991);
  eTight_idisoSF_.push_back(0.999);
  
  
  eVeto_idisoDataEff_.push_back(0.434);
  eVeto_idisoDataEff_.push_back(0.635);
  eVeto_idisoDataEff_.push_back(0.799);
  eVeto_idisoDataEff_.push_back(0.891);
  eVeto_idisoDataEff_.push_back(0.926);
  eVeto_idisoDataEff_.push_back(0.935);
  eVeto_idisoDataEff_.push_back(0.565);
  eVeto_idisoDataEff_.push_back(0.698);
  eVeto_idisoDataEff_.push_back(0.804);
  eVeto_idisoDataEff_.push_back(0.902);
  eVeto_idisoDataEff_.push_back(0.942);
  eVeto_idisoDataEff_.push_back(0.95 );
  eVeto_idisoDataEff_.push_back(0.49 );
  eVeto_idisoDataEff_.push_back(0.519);
  eVeto_idisoDataEff_.push_back(0.652);
  eVeto_idisoDataEff_.push_back(0.794);
  eVeto_idisoDataEff_.push_back(0.898);
  eVeto_idisoDataEff_.push_back(0.92 );
  eVeto_idisoDataEff_.push_back(0.357);
  eVeto_idisoDataEff_.push_back(0.546);
  eVeto_idisoDataEff_.push_back(0.741);
  eVeto_idisoDataEff_.push_back(0.872);
  eVeto_idisoDataEff_.push_back(0.93 );
  eVeto_idisoDataEff_.push_back(0.945);
  eVeto_idisoDataEff_.push_back(0.429);
  eVeto_idisoDataEff_.push_back(0.582);
  eVeto_idisoDataEff_.push_back(0.747);
  eVeto_idisoDataEff_.push_back(0.845);
  eVeto_idisoDataEff_.push_back(0.892);
  eVeto_idisoDataEff_.push_back(0.909);
  
  eVeto_idisoMCEff_.push_back(0.504);
  eVeto_idisoMCEff_.push_back(0.666);
  eVeto_idisoMCEff_.push_back(0.807);
  eVeto_idisoMCEff_.push_back(0.887);
  eVeto_idisoMCEff_.push_back(0.920);
  eVeto_idisoMCEff_.push_back(0.928);
  eVeto_idisoMCEff_.push_back(0.590);
  eVeto_idisoMCEff_.push_back(0.716);
  eVeto_idisoMCEff_.push_back(0.827);
  eVeto_idisoMCEff_.push_back(0.912);
  eVeto_idisoMCEff_.push_back(0.948);
  eVeto_idisoMCEff_.push_back(0.957);
  eVeto_idisoMCEff_.push_back(0.482);
  eVeto_idisoMCEff_.push_back(0.556);
  eVeto_idisoMCEff_.push_back(0.653);
  eVeto_idisoMCEff_.push_back(0.812);
  eVeto_idisoMCEff_.push_back(0.918);
  eVeto_idisoMCEff_.push_back(0.924);
  eVeto_idisoMCEff_.push_back(0.378);
  eVeto_idisoMCEff_.push_back(0.585);
  eVeto_idisoMCEff_.push_back(0.782);
  eVeto_idisoMCEff_.push_back(0.895);
  eVeto_idisoMCEff_.push_back(0.941);
  eVeto_idisoMCEff_.push_back(0.956);
  eVeto_idisoMCEff_.push_back(0.411);
  eVeto_idisoMCEff_.push_back(0.607);
  eVeto_idisoMCEff_.push_back(0.759);
  eVeto_idisoMCEff_.push_back(0.854);
  eVeto_idisoMCEff_.push_back(0.898);
  eVeto_idisoMCEff_.push_back(0.919);
  
  muTight_idSF_.push_back(0.970275);
  muTight_idSF_.push_back(0.988865);
  muTight_idSF_.push_back(0.992338);
  muTight_idSF_.push_back(0.993283);
  muTight_idSF_.push_back(0.993662);
  muTight_idSF_.push_back(0.992392);
  muTight_idSF_.push_back(0.99119 );
  muTight_idSF_.push_back(0.989417);
  muTight_idSF_.push_back(1.00375 );
  muTight_idSF_.push_back(1.0185  );
  muTight_idSF_.push_back(1.00173 );
  muTight_idSF_.push_back(0.993947);
  muTight_idSF_.push_back(0.994722);
  muTight_idSF_.push_back(0.993391);
  muTight_idSF_.push_back(0.992285);
  muTight_idSF_.push_back(0.99187 );
  muTight_idSF_.push_back(0.99501 );
  muTight_idSF_.push_back(0.990406);
  muTight_idSF_.push_back(1.00903 );
  muTight_idSF_.push_back(1.01096 );
  muTight_idSF_.push_back(1.01802 );
  muTight_idSF_.push_back(1.00035 );
  muTight_idSF_.push_back(0.998486);
  muTight_idSF_.push_back(0.996558);
  muTight_idSF_.push_back(0.996026);
  muTight_idSF_.push_back(0.996062);
  muTight_idSF_.push_back(0.995183);
  muTight_idSF_.push_back(0.992486);
  muTight_idSF_.push_back(1.02313 );
  muTight_idSF_.push_back(0.974754);
  
  muTight_isoSF_.push_back(0.940338);
  muTight_isoSF_.push_back(0.976738);
  muTight_isoSF_.push_back(0.996173);
  muTight_isoSF_.push_back(0.993228);
  muTight_isoSF_.push_back(0.993713);
  muTight_isoSF_.push_back(0.994084);
  muTight_isoSF_.push_back(0.996435);
  muTight_isoSF_.push_back(0.998658);
  muTight_isoSF_.push_back(1.00033 );
  muTight_isoSF_.push_back(0.998813);
  muTight_isoSF_.push_back(0.948434);
  muTight_isoSF_.push_back(0.986367);
  muTight_isoSF_.push_back(1.00036 );
  muTight_isoSF_.push_back(1.00009 );
  muTight_isoSF_.push_back(0.999092);
  muTight_isoSF_.push_back(0.998868);
  muTight_isoSF_.push_back(0.99789 );
  muTight_isoSF_.push_back(0.999215);
  muTight_isoSF_.push_back(1.00142 );
  muTight_isoSF_.push_back(1.00185 );
  muTight_isoSF_.push_back(0.972437);
  muTight_isoSF_.push_back(0.990054);
  muTight_isoSF_.push_back(1.00282 );
  muTight_isoSF_.push_back(1.00405 );
  muTight_isoSF_.push_back(1.00215 );
  muTight_isoSF_.push_back(1.00092 );
  muTight_isoSF_.push_back(1.0004  );
  muTight_isoSF_.push_back(1.0005  );
  muTight_isoSF_.push_back(0.999158);
  muTight_isoSF_.push_back(0.99644 );
  
  muVeto_idDataEff_.push_back(0.970558);
  muVeto_idDataEff_.push_back(0.983094);
  muVeto_idDataEff_.push_back(0.990864);
  muVeto_idDataEff_.push_back(0.994367);
  muVeto_idDataEff_.push_back(0.995233);
  muVeto_idDataEff_.push_back(0.996086);
  muVeto_idDataEff_.push_back(0.993125);
  muVeto_idDataEff_.push_back(0.985601);
  muVeto_idDataEff_.push_back(0.996936);
  muVeto_idDataEff_.push_back(0.991479);
  muVeto_idDataEff_.push_back(1       );
  muVeto_idDataEff_.push_back(0.996028);
  muVeto_idDataEff_.push_back(0.995377);
  muVeto_idDataEff_.push_back(0.995204);
  muVeto_idDataEff_.push_back(0.996528);
  muVeto_idDataEff_.push_back(0.99616 );
  muVeto_idDataEff_.push_back(0.994914);
  muVeto_idDataEff_.push_back(0.987736);
  muVeto_idDataEff_.push_back(0.998666);
  muVeto_idDataEff_.push_back(1       );
  muVeto_idDataEff_.push_back(1       );
  muVeto_idDataEff_.push_back(0.999848);
  muVeto_idDataEff_.push_back(0.99503 );
  muVeto_idDataEff_.push_back(0.99514 );
  muVeto_idDataEff_.push_back(0.995271);
  muVeto_idDataEff_.push_back(0.995194);
  muVeto_idDataEff_.push_back(0.99224 );
  muVeto_idDataEff_.push_back(0.980924);
  muVeto_idDataEff_.push_back(1       );
  muVeto_idDataEff_.push_back(0.985374);
  
  muVeto_isoDataEff_.push_back(0.825971);
  muVeto_isoDataEff_.push_back(0.90314 );
  muVeto_isoDataEff_.push_back(0.941507);
  muVeto_isoDataEff_.push_back(0.96178 );
  muVeto_isoDataEff_.push_back(0.976372);
  muVeto_isoDataEff_.push_back(0.987961);
  muVeto_isoDataEff_.push_back(0.992475);
  muVeto_isoDataEff_.push_back(0.99462 );
  muVeto_isoDataEff_.push_back(0.995887);
  muVeto_isoDataEff_.push_back(0.996746);
  muVeto_isoDataEff_.push_back(0.860547);
  muVeto_isoDataEff_.push_back(0.925161);
  muVeto_isoDataEff_.push_back(0.95403 );
  muVeto_isoDataEff_.push_back(0.968747);
  muVeto_isoDataEff_.push_back(0.982063);
  muVeto_isoDataEff_.push_back(0.991735);
  muVeto_isoDataEff_.push_back(0.994523);
  muVeto_isoDataEff_.push_back(0.995979);
  muVeto_isoDataEff_.push_back(0.997672);
  muVeto_isoDataEff_.push_back(0.998402);
  muVeto_isoDataEff_.push_back(0.887692);
  muVeto_isoDataEff_.push_back(0.944289);
  muVeto_isoDataEff_.push_back(0.966458);
  muVeto_isoDataEff_.push_back(0.977414);
  muVeto_isoDataEff_.push_back(0.98619 );
  muVeto_isoDataEff_.push_back(0.993596);
  muVeto_isoDataEff_.push_back(0.99581 );
  muVeto_isoDataEff_.push_back(0.996011);
  muVeto_isoDataEff_.push_back(0.996488);
  muVeto_isoDataEff_.push_back(0.996533);
  
  muVeto_idMCEff_.push_back(0.994928);
  muVeto_idMCEff_.push_back(0.996848);
  muVeto_idMCEff_.push_back(0.997477);
  muVeto_idMCEff_.push_back(0.99759 );
  muVeto_idMCEff_.push_back(0.997785);
  muVeto_idMCEff_.push_back(0.997884);
  muVeto_idMCEff_.push_back(0.998073);
  muVeto_idMCEff_.push_back(0.997947);
  muVeto_idMCEff_.push_back(0.998008);
  muVeto_idMCEff_.push_back(0.989194);
  muVeto_idMCEff_.push_back(0.995493);
  muVeto_idMCEff_.push_back(0.996791);
  muVeto_idMCEff_.push_back(0.99647 );
  muVeto_idMCEff_.push_back(0.997706);
  muVeto_idMCEff_.push_back(0.997892);
  muVeto_idMCEff_.push_back(0.998049);
  muVeto_idMCEff_.push_back(0.99789 );
  muVeto_idMCEff_.push_back(0.998271);
  muVeto_idMCEff_.push_back(0.997618);
  muVeto_idMCEff_.push_back(0.995712);
  muVeto_idMCEff_.push_back(0.9978  );
  muVeto_idMCEff_.push_back(0.996668);
  muVeto_idMCEff_.push_back(0.996883);
  muVeto_idMCEff_.push_back(0.997111);
  muVeto_idMCEff_.push_back(0.997046);
  muVeto_idMCEff_.push_back(0.996839);
  muVeto_idMCEff_.push_back(0.99738 );
  muVeto_idMCEff_.push_back(0.996821);
  muVeto_idMCEff_.push_back(0.99572 );
  muVeto_idMCEff_.push_back(1       );
  
  muVeto_isoMCEff_.push_back(0.861684);
  muVeto_isoMCEff_.push_back(0.913932);
  muVeto_isoMCEff_.push_back(0.941983);
  muVeto_isoMCEff_.push_back(0.962969);
  muVeto_isoMCEff_.push_back(0.977812);
  muVeto_isoMCEff_.push_back(0.989446);
  muVeto_isoMCEff_.push_back(0.993223);
  muVeto_isoMCEff_.push_back(0.994157);
  muVeto_isoMCEff_.push_back(0.995143);
  muVeto_isoMCEff_.push_back(0.995845);
  muVeto_isoMCEff_.push_back(0.890571);
  muVeto_isoMCEff_.push_back(0.934934);
  muVeto_isoMCEff_.push_back(0.951967);
  muVeto_isoMCEff_.push_back(0.966528);
  muVeto_isoMCEff_.push_back(0.980882);
  muVeto_isoMCEff_.push_back(0.991506);
  muVeto_isoMCEff_.push_back(0.994623);
  muVeto_isoMCEff_.push_back(0.995025);
  muVeto_isoMCEff_.push_back(0.996481);
  muVeto_isoMCEff_.push_back(0.994388);
  muVeto_isoMCEff_.push_back(0.903563);
  muVeto_isoMCEff_.push_back(0.949138);
  muVeto_isoMCEff_.push_back(0.964054);
  muVeto_isoMCEff_.push_back(0.97458 );
  muVeto_isoMCEff_.push_back(0.984299);
  muVeto_isoMCEff_.push_back(0.993538);
  muVeto_isoMCEff_.push_back(0.995586);
  muVeto_isoMCEff_.push_back(0.995768);
  muVeto_isoMCEff_.push_back(0.996599);
  muVeto_isoMCEff_.push_back(0.999177);
  
  for (unsigned iBin(0); iBin<muTight_idSF_.size();++iBin){
    muTight_idisoSF_.push_back(muTight_idSF_[iBin]*muTight_isoSF_[iBin]);
    if(muVeto_idDataEff_ [iBin]>1) muVeto_idDataEff_ [iBin]=1;
    if(muVeto_isoDataEff_[iBin]>1) muVeto_isoDataEff_[iBin]=1;
    if(muVeto_idMCEff_   [iBin]>1) muVeto_idMCEff_   [iBin]=1;
    if(muVeto_isoMCEff_  [iBin]>1) muVeto_isoMCEff_  [iBin]=1;
    if(muVeto_idDataEff_ [iBin]<0) muVeto_idDataEff_ [iBin]=0;
    if(muVeto_isoDataEff_[iBin]<0) muVeto_isoDataEff_[iBin]=0;
    if(muVeto_idMCEff_   [iBin]<0) muVeto_idMCEff_   [iBin]=0;
    if(muVeto_isoMCEff_  [iBin]<0) muVeto_isoMCEff_  [iBin]=0;
    muVeto_idisoDataEff_.push_back(muVeto_idDataEff_[iBin]*muVeto_isoDataEff_[iBin]);
    muVeto_idisoMCEff_  .push_back(muVeto_idMCEff_  [iBin]*muVeto_isoMCEff_  [iBin]);
  }
  
  for (unsigned iBin(0); iBin<eVeto_idisoDataEff_.size();++iBin){
    if(eVeto_idisoDataEff_[iBin]>1)eVeto_idisoDataEff_[iBin]=1;
    if(eVeto_idisoMCEff_  [iBin]>1)eVeto_idisoMCEff_  [iBin]=1;
    if(eVeto_idisoDataEff_[iBin]<0)eVeto_idisoDataEff_[iBin]=0;
    if(eVeto_idisoMCEff_  [iBin]<0)eVeto_idisoMCEff_  [iBin]=0;
  }

}

hepfw::WeightsLepton::~WeightsLepton(){
  
}

void hepfw::WeightsLepton::produce(hepfw::Event &event){
  
  //ID+iso tight leptons
  if(m_do_idiso_tight_weights){
    ic::ElectronCollection *elecs = event.getByName<ic::ElectronCollection>("electronsClean_CutBased_Tight");
    
    double ele_weight = 1.0;
    for (unsigned iEle=0; iEle<elecs->size();iEle++){
      ic::Electron *myElectron = &(*elecs)[iEle];
      unsigned iBin = findElectronPtEtaBin(myElectron->pt(),myElectron->eta());
      ele_weight *= eTight_idisoSF_[iBin];
    }
    
    ic::MuonCollection *mus = event.getByName<ic::MuonCollection>("muons_Tight");
    double mu_weight = 1.0;
    for (unsigned iEle=0; iEle<mus->size();iEle++){
      ic::Muon *myMuon = &(*mus)[iEle];
      unsigned iBin = findMuonPtEtaBin(myMuon->pt(),myMuon->eta());
      mu_weight *= muTight_idisoSF_[iBin];
    }
    
    event.addWeight("weight_idisoTight",ele_weight*mu_weight);
  }
  
  //TO DO: id+iso veto leptons
  //first try: take leptons from W in pT,eta acceptance
  
  if(m_do_idiso_veto_weights){
    
    vector<ic::GenParticle> *genParts = event.getByName< vector<ic::GenParticle> >("genParticles");
    double ele_veto_weight = 1.0;
    double mu_veto_weight  = 1.0;
    
    for (unsigned iEle=0; iEle<genParts->size(); iEle++){//loop on genparticles
      
      ic::GenParticle *myGenParticle = &(*genParts)[iEle];
      
      if (myGenParticle->status()!=3){continue;}
      
      //do Electrons
      if (abs(myGenParticle->pdgid())==11){
        
        if (myGenParticle->pt() > 10 && fabs(myGenParticle->eta()) < 2.4) {
          unsigned iBin = findElectronPtEtaBin(myGenParticle->pt(),myGenParticle->eta());
          ele_veto_weight *= (1-eVeto_idisoDataEff_[iBin])/(1-eVeto_idisoMCEff_[iBin]);
        }
      }
      
      //doMuons
      if (abs(myGenParticle->pdgid())==13){
        
        if (myGenParticle->pt() > 10 && fabs(myGenParticle->eta()) < 2.1) {
          unsigned iBin = findMuonPtEtaBin(myGenParticle->pt(),myGenParticle->eta());
          mu_veto_weight *= (1-muVeto_idisoDataEff_[iBin])/(1-muVeto_idisoMCEff_[iBin]);
          
        }
      }
      
      //doTaus
      if (abs(myGenParticle->pdgid())==15){
        
        //get the specific taus collection with daughters filled
        vector<ic::GenParticle> *taus = event.getByName< vector<ic::GenParticle> >("genParticlesTaus");
        
        for (unsigned j=0; j<taus->size(); j++) {
          ic::GenParticle *myGenTauSon = &(*taus)[j];
          
          unsigned idDau = abs(myGenTauSon->pdgid());
          
          if (idDau==11) {
            if (myGenTauSon->pt() > 10 && fabs(myGenTauSon->eta()) < 2.4){
              unsigned iBin = findElectronPtEtaBin(myGenTauSon->pt(),myGenTauSon->eta());
              ele_veto_weight *= (1-eVeto_idisoDataEff_[iBin])/(1-eVeto_idisoMCEff_[iBin]);
            }
          }
          if (idDau==13) {
            if (myGenTauSon->pt() > 10 && fabs(myGenTauSon->eta()) < 2.1){
              unsigned iBin = findMuonPtEtaBin(myGenTauSon->pt(),myGenTauSon->eta());
              mu_veto_weight *= (1-muVeto_idisoDataEff_[iBin])/(1-muVeto_idisoMCEff_[iBin]);
            }
          }
        }
      }
    
    }//loop on genparticles

    event.addWeight("weight_idisoVeto",ele_veto_weight*mu_veto_weight);
  }
}


void hepfw::WeightsLepton::fillVector(const std::string & aFileName, std::vector<double> & aVector){
  std::ifstream lInput;
  lInput.open(aFileName);
  if(!lInput.is_open()) {
    std::cerr << "Unable to open file: " << aFileName << ". Setting vector content to 1." << std::endl;
    //max expected size for e and mu is 33...
    aVector.resize(33,1);
    return;
  }
  while(1){
    double pTmin = 0;
    double pTmax = 0;
    double etaMin = 0;
    double etaMax = 0;
    double SF = 0;
    double SFerrPlus = 0;
    double SFerrMinus = 0;
    lInput>>pTmin>>pTmax>>etaMin>>etaMax>>SF>>SFerrMinus>>SFerrPlus;
    //protect against blank line at the end of the file
    if (pTmin > 1) aVector.push_back(SF);
    if(lInput.eof()){
      break; 
    }
  }
  
  std::cout << " ---- Size of vector for file " << aFileName << " = " << aVector.size() << std::endl;
  lInput.close();
  
}

unsigned hepfw::WeightsLepton::findElectronPtEtaBin(double pt, double eta){
  
  unsigned etaBin = 0;
  if (fabs(eta) < 0.8) etaBin=0;
  else if (fabs(eta) < 1.442) etaBin=1;
  else if (fabs(eta) < 1.556) etaBin=2;
  else if (fabs(eta) < 2.0) etaBin=3;
  else etaBin=4;
  unsigned ptBin = 0;
  if (pt<15) ptBin=0;
  else if (pt<20) ptBin=1;
  else if (pt<30) ptBin=2;
  else if (pt<40) ptBin=3;
  else if (pt<50) ptBin=4;
  else ptBin=5;
  
  return 6*etaBin+ptBin;
  
}

unsigned hepfw::WeightsLepton::findMuonPtEtaBin(double pt, double eta){
  unsigned etaBin = 0;
  if (fabs(eta) < 0.9) etaBin=0;
  else if (fabs(eta) < 1.2) etaBin=1;
  else etaBin=2;
  
  unsigned ptBin = 0;
  if (pt<20) ptBin=0;
  else if (pt<25) ptBin=1;
  else if (pt<30) ptBin=2;
  else if (pt<35) ptBin=3;
  else if (pt<40) ptBin=4;
  else if (pt<50) ptBin=5;
  else if (pt<60) ptBin=6;
  else if (pt<90) ptBin=7;
  else if (pt<140) ptBin=8;
  else if (pt<300) ptBin=9;
  else ptBin=10;
  
  return 11*etaBin+ptBin;
}
/*

doidisoeff=true
doidisoerr=false
doidisoerrmuore=true
doidisoerrupordown=false

HinvWeights hinvWeights = HinvWeights("HinvWeights")
.set_era(era)
.set_mc(mc)
.set_save_weights(true)
.set_do_top_reweighting(dotopreweighting)
.set_do_trg_weights(false)
.set_trg_applied_in_mc(false)
.set_do_idiso_tight_weights(false)
.set_do_idiso_veto_weights(false)
.set_do_idiso_err(false)
.set_do_idiso_errupordown(false)
.set_do_idiso_errmuore(true)
.set_fs(fs)
.set_input_met("metNoMuons");

if (!is_data) {
  hinvWeights.set_do_trg_weights(dotrgeff)
  .set_do_3dtrg_weights(do3dtrgeff)
  .set_do_1dparkedtrg_weights(do1dparkedtrgeff)
  .set_do_fitted1dparkedtrg_weights(dofitted1dparkedtrgeff)
  .set_do_binnedin2d1dfittedtrg_weights(dobinnedin2d1dtrgeff)
  .set_trg_weight_file(trg_weight_file)
  .set_trg_applied_in_mc(true);
  if(do3dtrgeff){
    hinvWeights.set_Alumi(0.889)
    .set_BClumi(11.023)
    .set_Dlumi(7.315);
  }
  hinvWeights.set_do_idiso_veto_weights(false);
  hinvWeights.set_do_idiso_tight_weights(false);
}

fillVector("data/scale_factors/ele_tight_id_with_syst.txt",eTight_idisoSF_);
fillVector("data/scale_factors/ele_veto_id_data_eff_with_syst.txt",eVeto_idisoDataEff_);
fillVector("data/scale_factors/ele_veto_id_mc_eff.txt",eVeto_idisoMCEff_);

fillVectorError("data/scale_factors/mu_tight_id_SF.txt",muTight_idSF_,do_idiso_errupordown_);
fillVectorError("data/scale_factors/mu_tight_iso_SF.txt",muTight_isoSF_,do_idiso_errupordown_);
fillVectorError("data/scale_factors/mu_loose_id_data_eff.txt",muVeto_idDataEff_,do_idiso_errupordown_);
fillVectorError("data/scale_factors/mu_loose_iso_data_eff.txt",muVeto_isoDataEff_,do_idiso_errupordown_);
fillVectorError("data/scale_factors/mu_loose_id_mc_eff.txt",muVeto_idMCEff_,do_idiso_errupordown_);
fillVectorError("data/scale_factors/mu_loose_iso_mc_eff.txt",muVeto_isoMCEff_,do_idiso_errupordown_);  

*/
