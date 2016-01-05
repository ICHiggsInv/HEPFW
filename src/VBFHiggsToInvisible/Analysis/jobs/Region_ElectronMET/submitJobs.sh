#!/bin/bash

# VBF Higgs to Invisible
cd MC_Powheg-Htoinv-mH110; ./submitJobs.sh; cd -;
cd MC_Powheg-Htoinv-mH125; ./submitJobs.sh; cd -;
cd MC_Powheg-Htoinv-mH150; ./submitJobs.sh; cd -;
cd MC_Powheg-Htoinv-mH200; ./submitJobs.sh; cd -;
cd MC_Powheg-Htoinv-mH300; ./submitJobs.sh; cd -;
cd MC_Powheg-Htoinv-mH400; ./submitJobs.sh; cd -;

# Gluon Fusion Higgs to Invisible
cd MC_Powheg-ggHtoinv-mH110; ./submitJobs.sh; cd -;
cd MC_Powheg-ggHtoinv-mH125; ./submitJobs.sh; cd -;
cd MC_Powheg-ggHtoinv-mH150; ./submitJobs.sh; cd -;
cd MC_Powheg-ggHtoinv-mH200; ./submitJobs.sh; cd -;
cd MC_Powheg-ggHtoinv-mH300; ./submitJobs.sh; cd -;
cd MC_Powheg-ggHtoinv-mH400; ./submitJobs.sh; cd -;

# WJets
cd MC_WJetsToLNu-v1; ./submitJobs.sh; cd -;
cd MC_WJetsToLNu-v2; ./submitJobs.sh; cd -;
cd MC_W1JetsToLNu; ./submitJobs.sh; cd -;
cd MC_W2JetsToLNu; ./submitJobs.sh; cd -;
cd MC_W3JetsToLNu; ./submitJobs.sh; cd -;
cd MC_W4JetsToLNu; ./submitJobs.sh; cd -;
cd MC_EWK-W2jminus; ./submitJobs.sh; cd -;
cd MC_EWK-W2jplus; ./submitJobs.sh; cd -;
# WJets -> electron
cd MC_WJetsToLNu-v1_electron; ./submitJobs.sh; cd -;
cd MC_WJetsToLNu-v2_electron; ./submitJobs.sh; cd -;
cd MC_W1JetsToLNu_electron; ./submitJobs.sh; cd -;
cd MC_W2JetsToLNu_electron; ./submitJobs.sh; cd -;
cd MC_W3JetsToLNu_electron; ./submitJobs.sh; cd -;
cd MC_W4JetsToLNu_electron; ./submitJobs.sh; cd -;
cd MC_EWK-W2jminus_electron; ./submitJobs.sh; cd -;
cd MC_EWK-W2jplus_electron; ./submitJobs.sh; cd -;
# WJets -> muon
cd MC_WJetsToLNu-v1_muon; ./submitJobs.sh; cd -;
cd MC_WJetsToLNu-v2_muon; ./submitJobs.sh; cd -;
cd MC_W1JetsToLNu_muon; ./submitJobs.sh; cd -;
cd MC_W2JetsToLNu_muon; ./submitJobs.sh; cd -;
cd MC_W3JetsToLNu_muon; ./submitJobs.sh; cd -;
cd MC_W4JetsToLNu_muon; ./submitJobs.sh; cd -;
cd MC_EWK-W2jminus_muon; ./submitJobs.sh; cd -;
cd MC_EWK-W2jplus_muon; ./submitJobs.sh; cd -;
# WJets -> tau
cd MC_WJetsToLNu-v1_tau; ./submitJobs.sh; cd -;
cd MC_WJetsToLNu-v2_tau; ./submitJobs.sh; cd -;
cd MC_W1JetsToLNu_tau; ./submitJobs.sh; cd -;
cd MC_W2JetsToLNu_tau; ./submitJobs.sh; cd -;
cd MC_W3JetsToLNu_tau; ./submitJobs.sh; cd -;
cd MC_W4JetsToLNu_tau; ./submitJobs.sh; cd -;
cd MC_EWK-W2jminus_tau; ./submitJobs.sh; cd -;
cd MC_EWK-W2jplus_tau; ./submitJobs.sh; cd -;

# Z/Z* to leptons  samples
cd MC_DYJetsToLL_PtZ-100-madgraph; ./submitJobs.sh; cd -;
cd MC_DYJetsToLL; ./submitJobs.sh; cd -;
cd MC_DY1JetsToLL; ./submitJobs.sh; cd -;
cd MC_DY2JetsToLL; ./submitJobs.sh; cd -;
cd MC_DY3JetsToLL; ./submitJobs.sh; cd -;
cd MC_DY4JetsToLL; ./submitJobs.sh; cd -;
cd MC_EWK-Z2j; ./submitJobs.sh; cd -;

# Z/Z* to nu nu samples
cd MC_ZJetsToNuNu_50_HT_100; ./submitJobs.sh; cd -;
cd MC_ZJetsToNuNu_100_HT_200; ./submitJobs.sh; cd -;
cd MC_ZJetsToNuNu_200_HT_400; ./submitJobs.sh; cd -;
cd MC_ZJetsToNuNu_400_HT_inf; ./submitJobs.sh; cd -;

# VV samples
cd MC_WW; ./submitJobs.sh; cd -;
cd MC_WZ; ./submitJobs.sh; cd -;
cd MC_ZZ; ./submitJobs.sh; cd -;

# Single top samples
cd MC_SingleT-s; ./submitJobs.sh; cd -;
cd MC_SingleT-t; ./submitJobs.sh; cd -;
cd MC_SingleTBar-s; ./submitJobs.sh; cd -;
cd MC_SingleTBar-t; ./submitJobs.sh; cd -;
cd MC_T-tW; ./submitJobs.sh; cd -;
cd MC_Tbar-tW; ./submitJobs.sh; cd -;

# TTbar samples
cd MC_TTJets; ./submitJobs.sh; cd -;

# Inclusive QCD Samples
cd MC_QCD-Pt-30to50; ./submitJobs.sh; cd -;
cd MC_QCD-Pt-50to80; ./submitJobs.sh; cd -;
cd MC_QCD-Pt-80to120; ./submitJobs.sh; cd -;
cd MC_QCD-Pt-120to170; ./submitJobs.sh; cd -;
cd MC_QCD-Pt-170to300; ./submitJobs.sh; cd -;
cd MC_QCD-Pt-300to470; ./submitJobs.sh; cd -;
cd MC_QCD-Pt-470to600; ./submitJobs.sh; cd -;
cd MC_QCD-Pt-600to800; ./submitJobs.sh; cd -;
cd MC_QCD-Pt-800to1000; ./submitJobs.sh; cd -;
cd MC_QCD-Pt-1000to1400; ./submitJobs.sh; cd -;
cd MC_QCD-Pt-1400to1800; ./submitJobs.sh; cd -;
cd MC_QCD-Pt-1800; ./submitJobs.sh; cd -;

# VBF QCD Samples
cd MC_QCD-Pt-80to120_VBF-MET40; ./submitJobs.sh; cd -;
cd MC_QCD-Pt-120to170_VBF-MET40; ./submitJobs.sh; cd -;
cd MC_QCD-Pt-170to300_VBF-MET40; ./submitJobs.sh; cd -;
cd MC_QCD-Pt-300to470_VBF-MET40; ./submitJobs.sh; cd -;
cd MC_QCD-Pt-470to600_VBF-MET40; ./submitJobs.sh; cd -;

# Prompt Data 
cd DATA_MET-2012A-22Jan2013-v1; ./submitJobs.sh; cd -;
cd DATA_MET-2012B-22Jan2013-v1; ./submitJobs.sh; cd -;
cd DATA_MET-2012C-22Jan2013-v1; ./submitJobs.sh; cd -;
cd DATA_MET-2012D-22Jan2013-v1; ./submitJobs.sh; cd -;

# Parked Data
cd DATA_VBF-Parked-2012B-22Jan2013-v1; ./submitJobs.sh; cd -;
cd DATA_VBF-Parked-2012C-22Jan2013-v1; ./submitJobs.sh; cd -;
cd DATA_VBF-Parked-2012D-22Jan2013-v1; ./submitJobs.sh; cd -;
