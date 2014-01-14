#Necessary to use shell built-in commands
SHELL      = bash
CXX        = g++
LD         = g++
MAKEDEPEND = g++ $(CXXFLAGS) -M

vpath %.h ../src
vpath %.cxx ../src

.PHONY: all objects lib clean

BASEDIR  = $(shell pwd)

# Define include paths
USERINCLUDES += -I$(ROOTSYS)/include/
USERINCLUDES += -I$(ROOFITSYS)/include/
# USERINCLUDES += -I$(CMS_PATH)/$(SCRAM_ARCH)/external/boost/1.47.0/include/
USERINCLUDES += -I$(realpath $(BASEDIR)/../src/)

# Define libraries to link
# USERLIBS += $(shell root-config --glibs) -lGenVector -lTreePlayer -lTMVA
# USERLIBS += -L$(ROOFITSYS)/lib/ -lRooFit -lRooFitCore
# USERLIBS += -L$(CMS_PATH)/$(SCRAM_ARCH)/external/boost/1.47.0/lib/ -lboost_regex -lboost_program_options -lboost_filesystem
# USERLIBS += -L$(CMSSW_BASE)/lib/$(SCRAM_ARCH) -lUserCodeICHiggsTauTau -lTauAnalysisCandidateTools
# USERLIBS += -L$(CMSSW_RELEASE_BASE)/lib/$(SCRAM_ARCH) -lFWCoreFWLite -lPhysicsToolsFWLite -lCommonToolsUtils

# CXXFLAGS = -Wall -W -Wno-unused-function -Wno-parentheses -Wno-char-subscripts -Wno-unused-parameter -O2 
CXXFLAGS  = -Wall -W -O2
CXXFLAGS += -Wno-deprecated-declarations
CXXFLAGS += -Wno-unused-parameter
CXXFLAGS += -Wno-unused-but-set-variable
CXXFLAGS += $(USERINCLUDES)

LDFLAGS  = -shared -Wall -W 

# File extensions
OBJ_EXT = o
EXE_EXT = exe
SRC_EXT = cxx
HEA_EXT = h

# Lists of packages, files and targets
PKGS = $(subst ../src/,,$(wildcard ../src/*))
SPKG = $(subst ../src/,,$(wildcard ../src/*/*))
SRCS = $(wildcard ../src/*/*/src/*.cxx)
HEAS = $(wildcard ../src/*/*/interface/*.h)
LIBS = $(patsubst %,libIC%.so,$(PKGS))
OBJS = $(subst ../src/,,$(subst $(SRC_EXT),$(OBJ_EXT),$(wildcard ../src/*/*/src/*.cxx)))
BINS = $(subst ../src/,,$(subst $(SRC_EXT),$(EXE_EXT),$(wildcard ../src/*/*/exe/*.cxx)))

-include $(OBJS:.o=.d)
-include $(BINS:.exe=.d)

all: | obj lib bin
	@echo "All done!"
	@echo ""

obj: $(OBJS)
	@echo "Objects done!"
	@echo ""

lib: $(LIBS)
	@echo "Libraries done!"
	@echo ""

bin: $(BINS)
	@echo "Binaries done!"
	@echo ""

%.o :  %.cxx
	@echo "----->Compiling object: " $@
	@$(shell mkdir -p $(dir $@);)
	@$(MAKEDEPEND) -MT $@ -o $*.d $<
	@$(CXX) $(CXXFLAGS) -fPIC -c $< -o $@

%.so : $(OBJS)
	@echo "----->Producing shared lib: " $@
	@$(LD) $(LDFLAGS) -o $@ $(filter $(subst %,%/,$(subst libIC,,$*))%,$(OBJS)) 

%.exe : %.cxx  $(LIBS) 
	@echo "----->Producing binary: " $@
	@$(shell mkdir -p $(dir $@);)
	@$(MAKEDEPEND) -MT $@ -o $*.d $<
	@$(CXX) -o $@ $(CXXFLAGS) $< $(LIBS) `root-config --cflags --libs`
	@$(shell ln -s $(BASEDIR)/$@ ../bin/$(notdir $(subst .exe,,$@));)

clean:
	@echo "-----> Cleaning Objects"
	@rm -r $(OBJS)
	@echo "-----> Cleaning Libraries"
	@rm -r $(LIBS)
	@echo "-----> Cleaning Binaries"
	@rm -f $(BINS)
	@$(foreach bin,$(BINS),rm -f ../bin/$(notdir $(subst .exe,,$(bin)));)

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
