ifndef HEPFWSYS
  $(error Variable HEPFWSYS is not set... Aborting)
endif


#Necessary to use shell built-in commands
SHELL      = bash
CXX        = g++
LD         = g++
MAKEDEPEND = g++ $(CXXFLAGS) -M

vpath %.h src/
vpath %.cxx src/

.PHONY: all dict obj lib bin docs clean test

BASEDIR  = $(shell pwd)

# Define include paths
USERINCLUDES += -I$(ROOTSYS)/include/
USERINCLUDES += -I$(ROOFITSYS)/include/
# USERINCLUDES += -I$(CMSSW_BASE)/src/
USERINCLUDES += -I$(CMS_PATH)/$(SCRAM_ARCH)/external/boost/1.47.0/include/
USERINCLUDES += -I$(realpath $(HEPFWSYS)/src/)

# Define libraries to link
USERLIBS += $(shell root-config --cflags --libs)
USERLIBS += -lGenVector -lTreePlayer -lTMVA
# USERLIBS += -L$(ROOFITSYS)/lib/ -lRooFit -lRooFitCore
USERLIBS += -L$(CMS_PATH)/$(SCRAM_ARCH)/external/boost/1.47.0/lib/ -lboost_regex -lboost_program_options -lboost_filesystem
USERLIBS += -L$(HEPFWSYS)/lib/
# USERLIBS += -L$(CMSSW_BASE)/lib/$(SCRAM_ARCH) -lUserCodeICHiggsTauTau
# USERLIBS += -L$(CMSSW_RELEASE_BASE)/lib/$(SCRAM_ARCH) -lFWCoreFWLite -lPhysicsToolsFWLite -lCommonToolsUtils

# CXXFLAGS = -Wall -W -Wno-unused-function -Wno-parentheses -Wno-char-subscripts -Wno-unused-parameter -O2
CXXFLAGS  = -g -W -Wall -O2 -fPIC `root-config --cflags`
# Next line is necessary to compile C++0x code with g++ 4.6.X
CXXFLAGS += -std=c++0x
CXXFLAGS += -Wno-deprecated-declarations
CXXFLAGS += -Wno-unused-parameter
CXXFLAGS += -Wno-unused-but-set-variable
CXXFLAGS += $(USERINCLUDES)

LDFLAGS  = -shared -W -Wall -fPIC `root-config --ldflags --cflags`

# File extensions
OBJ_EXT = o
EXE_EXT = exe
SRC_EXT = cxx
HEA_EXT = h

# Lists of packages, files and targets
PKGS = $(subst src/,,$(wildcard src/*))
SPKG = $(subst src/,,$(wildcard src/*/*))
SRCS = $(wildcard src/*/*/src/*.cxx)
HEAS = $(wildcard src/*/*/interface/*.h)
LIBS = $(patsubst %,lib/libHEPFW%.so,$(PKGS))
OBJS = $(patsubst src/%,lib/%,$(subst $(SRC_EXT),$(OBJ_EXT),$(wildcard src/*/*/src/*.cxx)))
BINS = $(subst src/,lib/,$(subst $(SRC_EXT),$(EXE_EXT),$(wildcard src/*/*/exe/*.cxx)))
DICT = src/DataFormats/ICHiggsTauTau/src/dict.cxx

# Pre-processing 
SCAN = src/FWCore/Framework/scan/ModulesScan.h src/FWCore/Framework/scan/PostProcessingModulesScan.h

-include $(OBJS:.o=.d)
-include $(BINS:.exe=.d)

all: | dict pre obj lib bin

# *** Scanning for new modules ***
# This is made over two stages:
# 1) Event modules scan
# 2) Post processing modules scan
#
# NOTE: The use of the python command is intended to use
# the CMSSW version of this command and not the system version 
# which is currently for my studies SLC5
pre: $(SCAN)

src/FWCore/Framework/scan/ModulesScan.h: $(HEAS)
	@python $(HEPFWSYS)/bin/hepfwModulesScan.py --EventProcessing

src/FWCore/Framework/scan/PostProcessingModulesScan.h: $(HEAS)
	@python $(HEPFWSYS)/bin/hepfwModulesScan.py --PostProcessing

# Making dictionaries
dict: $(DICT)

# TODO: Make this depend on the actual objects where for which dictionaries will be made
# This should be possible by running dependencies checker on the produced dict file after production
src/DataFormats/ICHiggsTauTau/src/dict.cxx: DataFormats/ICHiggsTauTau/Linkdef.h
	@cd src/; rootcint -f DataFormats/ICHiggsTauTau/src/dict.cxx -c -Wall -W -O2 -fPIC `root-config --cflags` -I$ROOTSYS/include -I./ -p DataFormats/ICHiggsTauTau/interface/* DataFormats/ICHiggsTauTau/Linkdef.h

# Building objects
obj: $(OBJS) $(SCAN) $(DICT)
	@echo "Objects done!"
	@echo ""

lib: $(LIBS) $(SCAN) $(DICT)
	@echo "Libraries done!"
	@echo ""

bin: $(BINS) $(SCAN) $(DICT)
	@echo "Binaries done!"
	@echo ""

# Rules to make objects and dependencies
lib/%.o : src/%.cxx
	@echo "----->Compiling object: " $@
	@$(shell mkdir -p $(dir $@);)
	@$(MAKEDEPEND) -MMD -o lib/$*.d $<
	@$(CXX) $(CXXFLAGS) -c $< -o $@

# Rules to make libraries
lib/%.so : $(OBJS)
	@echo "----->Producing shared lib: " $@
	@$(LD) $(LDFLAGS) -o $@ $(filter $(patsubst %,lib/%,$(subst libHEPFW,,$*))%,$(OBJS)) `root-config --glibs`

# Rules to make executables
lib/%.exe : src/%.cxx  $(LIBS)
	@echo "----->Producing binary: " $@
	@$(shell mkdir -p $(dir $@);)
	@$(MAKEDEPEND) -MMD -o lib/$*.d $<
	@$(shell rm -f bin/$(notdir $(subst .exe,,$@));)
	@$(CXX) -o $@ $(CXXFLAGS) $(USERLIBS) $(patsubst lib%.so,-l%,$(notdir $(LIBS))) $<
	@$(shell ln -s $(HEPFWSYS)/$@ bin/$(notdir $(subst .exe,,$@));)

clean:
	@echo "-----> Cleaning scan files"
	@rm -r $(SCAN)
	@echo "-----> Cleaning Objects"
	@rm -fR $(HEPFWSYS)/lib/*/
	@echo "-----> Cleaning Libraries"
	@rm -fR $(HEPFWSYS)/lib/*.so
	@echo "-----> Cleaning Binaries"
	@find bin/ -maxdepth 1 -type l -exec rm -f {} \;
	@echo "-----> Cleaning Documentation"
	@rm -fr ../html
 
docs:
	@$(shell doxygen lib/Doxyfile;)

test:
	@echo "PKGS : "$(PKGS)
	@echo "SKGS : "$(SPKG)
	@echo ""
	@echo "SRCS : "$(SRCS)
	@echo "HEAS : "$(HEAS)
	@echo "OBJS : "$(OBJS)
	@echo ""
	@echo "EXES : "$(EXES)
	@echo "BINS : "$(BINS)
	@echo ""
	@echo "LIBS : "$(LIBS)
