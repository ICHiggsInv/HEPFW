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
CXXFLAGS  = -Wall -W -O2 -std=c++0x 
CXXFLAGS += -Wno-deprecated-declarations
CXXFLAGS += -Wno-unused-parameter
CXXFLAGS += -Wno-unused-but-set-variable
CXXFLAGS += $(USERINCLUDES)

LDFLAGS  = -shared -Wall -W 

# A list of directories
BASEDIR  = $(shell pwd)
EXEDIR   = $(BASEDIR)/bin
OBJDIR   = $(BASEDIR)/obj
TESTDIR  = $(BASEDIR)/test
DOCDIR   = $(BASEDIR)/docs
CMSSWLIB = $(CMSSW_BASE)/lib/$(SCRAM_ARCH)
CMSSWBIN = $(CMSSW_BASE)/bin/$(SCRAM_ARCH)

# Build a list of srcs and bins to build

# File extensions
OBJ_EXT = o
SRC_EXT = cxx
HEA_EXT = h

SRCDIR = $(CMSSW_BASE)/src/ICTools
# LIBDIR = $(SRCDIR)/lib

PKGS = $(subst /src/,,$(wildcard */src/))
SRCS = $(wildcard */src/*.cxx)
HEAS = $(wildcard */interface/*.h)
EXES = $(wildcard */main/*.cxx)

OBJS = $(subst src/,obj/,$(subst $(SRCDIR),,$(subst $(SRC_EXT),$(OBJ_EXT),$(SRCS))))
LIBS = $(patsubst %,$(CMSSWLIB)/libICTools_%.so,$(PKGS))
BINS = $(addprefix $(CMSSWBIN)/,$(notdir $(subst .$(SRC_EXT),,$(EXES))))

all: dir $(LIBS) $(BINS)
	@echo "done!"

dir:
	@$(shell mkdir -p obj;)
	@$(foreach dir,$(PKGS),mkdir -p $(dir)/obj;)

test:
	@echo "SRCDIR   : "$(SRCDIR)
	@echo "PKGS     : "$(PKGS)
	@echo "SRCS     : "$(SRCS)
	@echo "EXES     : "$(EXES)
	@echo "OBJS     : "$(OBJS)
	@echo "BINS     : "$(BINS)
	@echo "LIBS     : "$(LIBS)
	@echo "CMSSWLIB : "$(CMSSWLIB)

docs: all
	doxygen Doxyfile

%.$(OBJ_EXT) : #$(SRCS) $(HEAS)
	@echo "----->Compiling object: " $@
	$(CXX) $(CXXFLAGS) -fPIC -c $(addsuffix .cxx,$(subst obj,src,$*)) -o $@
	@echo ""

$(CMSSWLIB)/libICTools_%.so : $(OBJS) 
	@echo "----->Producing shared lib: " $@
	@echo "----->Depends on: " $^
	@echo "----->Matches   : " $*
	@echo "----->Test      : " $(filter $*/obj/%,$(OBJS))
	$(LD) $(LDFLAGS) -o $@ $(filter $*/obj/%,$(OBJS)) 
	@echo ""

$(CMSSWBIN)/% : $(EXES) $(LIBS) $(HEAS)
	@echo "----->Compiling executable: " $@
	@echo "----->Depends on: " $^
	$(CXX) -o $@ $(CXXFLAGS) $(filter %/$*.cxx,$(EXES)) $(LIBS)  `root-config --cflags --libs`
# 	-L$(LIBDIR)
	@echo ""

clean:
	@echo "-----> Cleaning Objects:"
	rm -rf $(OBJS)
	@echo "-----> Cleaning Libraries:"
	rm -rf $(LIBS)
	@echo "-----> Cleaning Binaries:"
	rm -fr $(BINS)
