#!/bin/bash

rootcint -f DataFormats/ICHiggsTauTau/src/dict.cxx -c -Wall -W -O2 -fPIC `root-config --cflags` -I$ROOTSYS/include -I./ -p DataFormats/ICHiggsTauTau/interface/* DataFormats/ICHiggsTauTau/Linkdef.h
