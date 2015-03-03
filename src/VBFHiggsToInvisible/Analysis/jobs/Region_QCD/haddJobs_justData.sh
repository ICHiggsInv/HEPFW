#!/bin/bash

# Prompt Data 
hadd DATA_MET-2012A-22Jan2013-v1.root DATA_MET-2012A-22Jan2013-v1/results_Job*.root
hadd DATA_MET-2012B-22Jan2013-v1.root DATA_MET-2012B-22Jan2013-v1/results_Job*.root
hadd DATA_MET-2012C-22Jan2013-v1.root DATA_MET-2012C-22Jan2013-v1/results_Job*.root
hadd DATA_MET-2012D-22Jan2013-v1.root DATA_MET-2012D-22Jan2013-v1/results_Job*.root

# Parked Data
hadd DATA_VBF-Parked-2012B-22Jan2013-v1.root DATA_VBF-Parked-2012B-22Jan2013-v1/results_Job*.root
hadd DATA_VBF-Parked-2012C-22Jan2013-v1.root DATA_VBF-Parked-2012C-22Jan2013-v1/results_Job*.root
hadd DATA_VBF-Parked-2012D-22Jan2013-v1.root DATA_VBF-Parked-2012D-22Jan2013-v1/results_Job*.root
