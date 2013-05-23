#Necessary to use shell built-in commands
SHELL = bash
CXX   = g++
LD    = g++

.PHONY: clean

# Define include paths
USERINCLUDES += -I$(ROOTSYS)/include/
USERINCLUDES += -I$(ROOFITSYS)/include/
USERINCLUDES += -I$(CMS_PATH)/$(SCRAM_ARCH)/external/boost/1.47.0/include/
USERINCLUDES += -I$(CMSSW_BASE)/src/ 
USERINCLUDES += -I$(CMSSW_RELEASE_BASE)/src/

# Define libraries to link
USERLIBS += $(shell root-config --glibs) -lGenVector -lTreePlayer -lTMVA
USERLIBS += -L$(ROOFITSYS)/lib/ -lRooFit -lRooFitCore
USERLIBS += -L$(CMS_PATH)/$(SCRAM_ARCH)/external/boost/1.47.0/lib/ -lboost_regex -lboost_program_options -lboost_filesystem
USERLIBS += -L$(CMSSW_BASE)/lib/$(SCRAM_ARCH) -lUserCodeICHiggsTauTau -lTauAnalysisCandidateTools
USERLIBS += -L$(CMSSW_RELEASE_BASE)/lib/$(SCRAM_ARCH) -lFWCoreFWLite -lPhysicsToolsFWLite -lCommonToolsUtils

#CXXFLAGS = -Wall -W -Wno-unused-function -Wno-parentheses -Wno-char-subscripts -Wno-unused-parameter -O2 
CXXFLAGS = -Wall -W -O2 -std=c++0x -Wno-deprecated-declarations -Wno-unused-parameter
LDFLAGS  = -shared -Wall -W 

CXXFLAGS += $(USERINCLUDES)
LIBS     += $(USERLIBS)

# A list of directories
BASEDIR = $(shell pwd)
EXEDIR  = $(BASEDIR)/bin
OBJDIR  = $(BASEDIR)/obj
TESTDIR = $(BASEDIR)/test
DOCDIR  = $(BASEDIR)/docs

# Build a list of srcs and bins to build

# File extensions
OBJ_EXT = o
SRC_EXT = cxx

SRCDIR = $(CMSSW_BASE)/src/ICTools
LIBDIR = $(SRCDIR)/lib

PKGS = $(subst /src/,,$(wildcard */src/))
SRCS = $(wildcard */src/*.cxx)
EXES = $(wildcard */main/*.cxx)

OBJS = $(subst cxx,$(OBJ_EXT),$(SRCS))
LIBS = lib/lib$(PKGS).so

OBJS = $(subst src/,obj/,$(subst $(SRCDIR),,$(subst $(SRC_EXT),$(OBJ_EXT),$(SRCS))))
BINS = $(subst main/,bin/,$(subst $(PKGS)/,,$(subst .$(SRC_EXT),,$(EXES))))

# Making directories
$(shell mkdir -p lib)
$(shell mkdir -p bin)
$(shell mkdir -p $(PKGS)/obj)

test:
	@echo "SRCDIR: "$(SRCDIR)
	@echo "PKGS  : "$(PKGS)
	@echo "SRCS  : "$(SRCS)
	@echo "EXES  : "$(EXES)
	@echo "OBJS  : "$(OBJS)
	@echo "BINS  : "$(BINS)
	@echo "LIBS  : "$(LIBS)
	
# all:  lib $(BINS)
all: $(LIBS) $(BINS)

docs: all
	doxygen Doxyfile

$(PKGS)/obj/%.$(OBJ_EXT): $(PKGS)/src/%.$(SRC_EXT) $(PKGS)/interface/%.h
	@echo "----->Compiling object: " $@
	@echo "----->Depends on: " $^
	$(CXX) $(CXXFLAGS) -fPIC -c $<  -o $@
	@echo ""

lib/lib%.so: $(filter %,$(OBJS))
	@echo "----->Producing shared lib: " $@
	@echo "----->Depends on: " $^
	$(LD) $(LDFLAGS) -o $@ $(filter %,$(OBJS)) 
	@echo ""

bin/%: $(PKGS)/main/%.cxx lib/lib$(PKGS).so $(PKGS)/interface/*.h
	@echo "----->Compiling executable: " $@
	@echo "----->Depends on: " $^
	$(CXX) -o $@ $(CXXFLAGS) $< $(LIBS) -L$(LIBDIR) -l$(PKGS) `root-config --cflags --libs`
	@echo ""

clean:
	@echo "-----> Cleaning Objects:"
	rm -rf $(OBJS)
	@echo "-----> Cleaning Libraries:"
	rm -rf $(LIBS)
	@echo "-----> Cleaning Binaries:"
	rm -fr $(BINS)
