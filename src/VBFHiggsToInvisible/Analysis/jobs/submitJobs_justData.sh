#!/bin/bash

cd Region_ElectronMET/;  ./submitJobs_justData.sh; cd ..;
cd Region_MuonMET/;      ./submitJobs_justData.sh; cd ..;
cd Region_TauMET/;       ./submitJobs_justData.sh; cd ..;

cd Region_Zmumu/;        ./submitJobs_justData.sh; cd ..;
cd Region_Top/;          ./submitJobs_justData.sh; cd ..;
cd Region_QCD/;          ./submitJobs_justData.sh; cd ..;
cd Region_PreSelection/; ./submitJobs_justData.sh; cd ..;
cd Region_Signal/;       ./submitJobs_justData.sh; cd ..;
