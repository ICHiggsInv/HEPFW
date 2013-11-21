#Necessary to use shell built-in commands
SHELL = bash
CXX   = g++
LD    = g++

.PHONY: clean

BASEDIR  = $(shell pwd)

# Define include paths
USERINCLUDES += -I$(ROOTSYS)/include/
USERINCLUDES += -I$(ROOFITSYS)/include/
# USERINCLUDES += -I$(CMS_PATH)/$(SCRAM_ARCH)/external/boost/1.47.0/include/
USERINCLUDES += -I$(BASEDIR)/src/

# Define libraries to link
USERLIBS += $(shell root-config --glibs) -lGenVector -lTreePlayer -lTMVA
USERLIBS += -L$(ROOFITSYS)/lib/ -lRooFit -lRooFitCore
# USERLIBS += -L$(CMS_PATH)/$(SCRAM_ARCH)/external/boost/1.47.0/lib/ -lboost_regex -lboost_program_options -lboost_filesystem
# USERLIBS += -L$(CMSSW_BASE)/lib/$(SCRAM_ARCH) -lUserCodeICHiggsTauTau -lTauAnalysisCandidateTools
# USERLIBS += -L$(CMSSW_RELEASE_BASE)/lib/$(SCRAM_ARCH) -lFWCoreFWLite -lPhysicsToolsFWLite -lCommonToolsUtils

# CXXFLAGS = -Wall -W -Wno-unused-function -Wno-parentheses -Wno-char-subscripts -Wno-unused-parameter -O2 
CXXFLAGS  = -Wall -W -O2
CXXFLAGS += -Wno-deprecated-declarations
CXXFLAGS += -Wno-unused-parameter
# CXXFLAGS += -Wno-unused-but-set-variable
CXXFLAGS += $(USERINCLUDES)

LDFLAGS  = -shared -Wall -W 

# A list of directories
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

PKGS = $(subst src/,,$(wildcard src/*))
SPKG = $(subst src/,,$(wildcard src/*/*))
SRCS = $(wildcard src/*/*/src/*.cxx)
EXES = $(wildcard src/*/*/exe/*.cxx)
LIBS = $(patsubst %,lib/%.so,$(PKGS))
OBJS = $(subst src/,obj/,$(subst /src/,/,$(subst $(SRC_EXT),$(OBJ_EXT),$(wildcard src/*/*/src/*.cxx))))
BINS = $(addprefix bin/,$(notdir $(subst .$(SRC_EXT),,$(wildcard src/*/*/exe/*.cxx))))

all: dir $(OBJS) $(LIBS) $(BINS)
	@echo "done!"

dir:
	@$(shell mkdir -p lib;)
	@$(shell mkdir -p obj;)
	@$(shell mkdir -p bin;)
	@$(foreach dir,$(SPKG),mkdir -p obj/$(dir)/;)

test:
	@echo "PKGS : "$(PKGS)
	@echo "SKGS : "$(SPKG)
	@echo ""
	@echo "SRCS : "$(SRCS)
	@echo "OBJS : "$(OBJS)
	@echo ""
	@echo "EXES : "$(EXES)
	@echo "BINS : "$(BINS)	
	@echo ""
	@echo "LIBS : "$(LIBS)


%.$(OBJ_EXT) : #$(SRCS) $(HEAS)
	@echo "----->Compiling object: " $@
	$(CXX) $(CXXFLAGS) -fPIC -c $(filter %$(notdir $*.cxx),$(SRCS)) -o $@
	@echo ""

%.so : $(OBJS)
	@echo "----->Producing shared lib: " $@
	@echo $*
	$(LD) $(LDFLAGS) -o $@ $(filter obj/$(notdir $*)%,$(OBJS)) 
	@echo ""

bin/% : $(LIBS)
	@echo "----->Producing binary: " $@
	$(CXX) -o $@ $(CXXFLAGS) $(filter %$(notdir $*.cxx),$(EXES)) $(LIBS) `root-config --cflags --libs`

clean:
	@echo "-----> Cleaning Objects:"
	rm -rf $(OBJS)
	@echo "-----> Cleaning Libraries:"
	rm -rf $(LIBS)
	@echo "-----> Cleaning Binaries:"
	rm -fr $(BINS)
