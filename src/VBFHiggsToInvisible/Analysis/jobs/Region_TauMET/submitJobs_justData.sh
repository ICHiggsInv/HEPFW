#!/bin/bash

# Prompt Data 
cd DATA_MET-2012A-22Jan2013-v1; ./submitJobs.sh; cd -;
cd DATA_MET-2012B-22Jan2013-v1; ./submitJobs.sh; cd -;
cd DATA_MET-2012C-22Jan2013-v1; ./submitJobs.sh; cd -;
cd DATA_MET-2012D-22Jan2013-v1; ./submitJobs.sh; cd -;

# Parked Data
cd DATA_VBF-Parked-2012B-22Jan2013-v1; ./submitJobs.sh; cd -;
cd DATA_VBF-Parked-2012C-22Jan2013-v1; ./submitJobs.sh; cd -;
cd DATA_VBF-Parked-2012D-22Jan2013-v1; ./submitJobs.sh; cd -;
