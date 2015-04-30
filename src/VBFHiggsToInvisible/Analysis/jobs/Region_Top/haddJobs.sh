#!/bin/bash

# VBF Higgs to Invisible
hadd MC_Powheg-Htoinv-mH110.root MC_Powheg-Htoinv-mH110/results_Job*.root
hadd MC_Powheg-Htoinv-mH125.root MC_Powheg-Htoinv-mH125/results_Job*.root
hadd MC_Powheg-Htoinv-mH150.root MC_Powheg-Htoinv-mH150/results_Job*.root
hadd MC_Powheg-Htoinv-mH200.root MC_Powheg-Htoinv-mH200/results_Job*.root
hadd MC_Powheg-Htoinv-mH300.root MC_Powheg-Htoinv-mH300/results_Job*.root
hadd MC_Powheg-Htoinv-mH400.root MC_Powheg-Htoinv-mH400/results_Job*.root

# Gluon Fusion Higgs to Invisible
hadd MC_Powheg-ggHtoinv-mH110.root MC_Powheg-ggHtoinv-mH110/results_Job*.root
hadd MC_Powheg-ggHtoinv-mH125.root MC_Powheg-ggHtoinv-mH125/results_Job*.root
hadd MC_Powheg-ggHtoinv-mH150.root MC_Powheg-ggHtoinv-mH150/results_Job*.root
hadd MC_Powheg-ggHtoinv-mH200.root MC_Powheg-ggHtoinv-mH200/results_Job*.root
hadd MC_Powheg-ggHtoinv-mH300.root MC_Powheg-ggHtoinv-mH300/results_Job*.root
hadd MC_Powheg-ggHtoinv-mH400.root MC_Powheg-ggHtoinv-mH400/results_Job*.root

# WJets
hadd MC_WJetsToLNu-v1.root MC_WJetsToLNu-v1/results_Job*.root
hadd MC_WJetsToLNu-v2.root MC_WJetsToLNu-v2/results_Job*.root
hadd MC_W1JetsToLNu.root MC_W1JetsToLNu/results_Job*.root
hadd MC_W2JetsToLNu.root MC_W2JetsToLNu/results_Job*.root
hadd MC_W3JetsToLNu.root MC_W3JetsToLNu/results_Job*.root
hadd MC_W4JetsToLNu.root MC_W4JetsToLNu/results_Job*.root
hadd MC_EWK-W2jminus.root MC_EWK-W2jminus/results_Job*.root
hadd MC_EWK-W2jplus.root MC_EWK-W2jplus/results_Job*.root

# Z/Z* to leptons  samples
hadd MC_DYJetsToLL_PtZ-100.root MC_DYJetsToLL_PtZ-100/results_Job*.root
hadd MC_DYJetsToLL.root MC_DYJetsToLL/results_Job*.root
hadd MC_DY1JetsToLL.root MC_DY1JetsToLL/results_Job*.root
hadd MC_DY2JetsToLL.root MC_DY2JetsToLL/results_Job*.root
hadd MC_DY3JetsToLL.root MC_DY3JetsToLL/results_Job*.root
hadd MC_DY4JetsToLL.root MC_DY4JetsToLL/results_Job*.root
hadd MC_EWK-Z2j.root MC_EWK-Z2j/results_Job*.root

# Z/Z* to nu nu samples
# hadd MC_ZJetsToNuNu_50_HT_100.root MC_ZJetsToNuNu_50_HT_100/results_Job*.root
# hadd MC_ZJetsToNuNu_100_HT_200.root MC_ZJetsToNuNu_100_HT_200/results_Job*.root
# hadd MC_ZJetsToNuNu_200_HT_400.root MC_ZJetsToNuNu_200_HT_400/results_Job*.root
# hadd MC_ZJetsToNuNu_400_HT_inf.root MC_ZJetsToNuNu_400_HT_inf/results_Job*.root

# VV samples
hadd MC_WW.root MC_WW/results_Job*.root
hadd MC_WZ.root MC_WZ/results_Job*.root
hadd MC_ZZ.root MC_ZZ/results_Job*.root

# Single top samples
hadd MC_SingleT-s.root MC_SingleT-s/results_Job*.root
hadd MC_SingleT-t.root MC_SingleT-t/results_Job*.root
hadd MC_SingleTBar-s.root MC_SingleTBar-s/results_Job*.root
hadd MC_SingleTBar-t.root MC_SingleTBar-t/results_Job*.root
hadd MC_T-tW.root MC_T-tW/results_Job*.root
hadd MC_Tbar-tW.root MC_Tbar-tW/results_Job*.root

# TTbar samples
hadd MC_TTJets.root MC_TTJets/results_Job*.root

# Inclusive QCD Samples
hadd MC_QCD-Pt-30to50.root MC_QCD-Pt-30to50/results_Job*.root
hadd MC_QCD-Pt-50to80.root MC_QCD-Pt-50to80/results_Job*.root
hadd MC_QCD-Pt-80to120.root MC_QCD-Pt-80to120/results_Job*.root
hadd MC_QCD-Pt-120to170.root MC_QCD-Pt-120to170/results_Job*.root
hadd MC_QCD-Pt-170to300.root MC_QCD-Pt-170to300/results_Job*.root
hadd MC_QCD-Pt-300to470.root MC_QCD-Pt-300to470/results_Job*.root
hadd MC_QCD-Pt-470to600.root MC_QCD-Pt-470to600/results_Job*.root
hadd MC_QCD-Pt-600to800.root MC_QCD-Pt-600to800/results_Job*.root
hadd MC_QCD-Pt-800to1000.root MC_QCD-Pt-800to1000/results_Job*.root
hadd MC_QCD-Pt-1000to1400.root MC_QCD-Pt-1000to1400/results_Job*.root
hadd MC_QCD-Pt-1400to1800.root MC_QCD-Pt-1400to1800/results_Job*.root
hadd MC_QCD-Pt-1800.root MC_QCD-Pt-1800/results_Job*.root

# VBF QCD Samples
hadd MC_QCD-Pt-80to120_VBF-MET40.root  MC_QCD-Pt-80to120_VBF-MET40/results_Job*.root
hadd MC_QCD-Pt-120to170_VBF-MET40.root MC_QCD-Pt-120to170_VBF-MET40/results_Job*.root
hadd MC_QCD-Pt-170to300_VBF-MET40.root MC_QCD-Pt-170to300_VBF-MET40/results_Job*.root
hadd MC_QCD-Pt-300to470_VBF-MET40.root MC_QCD-Pt-300to470_VBF-MET40/results_Job*.root
hadd MC_QCD-Pt-470to600_VBF-MET40.root MC_QCD-Pt-470to600_VBF-MET40/results_Job*.root

# Prompt Data 
hadd DATA_MET-2012A-22Jan2013-v1.root DATA_MET-2012A-22Jan2013-v1/results_Job*.root
hadd DATA_MET-2012B-22Jan2013-v1.root DATA_MET-2012B-22Jan2013-v1/results_Job*.root
hadd DATA_MET-2012C-22Jan2013-v1.root DATA_MET-2012C-22Jan2013-v1/results_Job*.root
hadd DATA_MET-2012D-22Jan2013-v1.root DATA_MET-2012D-22Jan2013-v1/results_Job*.root

# Parked Data
hadd DATA_VBF-Parked-2012B-22Jan2013-v1.root DATA_VBF-Parked-2012B-22Jan2013-v1/results_Job*.root
hadd DATA_VBF-Parked-2012C-22Jan2013-v1.root DATA_VBF-Parked-2012C-22Jan2013-v1/results_Job*.root
hadd DATA_VBF-Parked-2012D-22Jan2013-v1.root DATA_VBF-Parked-2012D-22Jan2013-v1/results_Job*.root
