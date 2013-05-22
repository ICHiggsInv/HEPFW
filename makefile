#Necessary to use shell built-in commands
SHELL=bash

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
LDFLAGS = -shared -Wall -W 

# If possible we'll use the clang compiler, it's faster and gives more helpful error messages
# If it's not available, then fallback to gcc.
CXX=g++
LD=g++

# Update 17/2/2013:  Remove support for compiling with clang as there are issues with
# C++11

# CLANGPATH := $(shell type -p clang++)
# ifeq ($(CLANGPATH),)
# $(warning clang++ not found, reverting to g++!)
# CXX=g++
# LD=g++
# endif

CXXFLAGS += $(USERINCLUDES)
LIBS += $(USERLIBS)

# A list of directories
BASEDIR = $(shell pwd)
LIBDIR = $(BASEDIR)/lib
EXEDIR = $(BASEDIR)/bin
OBJDIR = $(BASEDIR)/obj
TESTDIR = $(BASEDIR)/test
DOCDIR= $(BASEDIR)/docs

# Build a list of srcs and bins to build

OBJ_EXT  = o
SRC_EXT = cxx

SRCDIR  = $(CMSSW_BASE)/src/ICTools

DIRS  = $(wildcard $(CMSSW_BASE)/src/ICTools/*/src/)
PKG   = $(subst /src/,,$(subst $(SRCDIR)/,,$(DIRS)))
SRCS  = $(wildcard $(SRCDIR)/*/src/*.cxx)
EXES  = $(wildcard $(SRCDIR)/*/main/*.cxx)

OBJS=$(subst cxx,$(OBJ_EXT),$(SRCS))
BINS=$(subst .$(SRC_EXT),,$(EXES))


OBJS = $(SRCDIR)$(subst src/,obj/,$(subst $(SRCDIR),,$(subst cxx,$(OBJ_EXT),$(SRCS))))
BINS = $(SRCDIR)$(subst main/,bin/,$(subst $(SRCDIR),,$(subst .$(SRC_EXT),,$(EXES))))

test:
	@echo "SRCDIR: "$(SRCDIR)
	@echo "PKG   : "$(PKG)
	@echo "SRCS  : "$(SRCS)
	@echo "BINS  : "$(EXES)
	@echo "OBJS  : "$(OBJS)
	@echo "BINS  : "$(BINS)

# all:  lib $(BINS)
all:  lib $(OBJS)

docs: all
	doxygen Doxyfile
	
$(EXEDIR)/%: $(TESTDIR)/%.cpp $(LIBDIR)/lib$(LIBNAME).so $(BASEDIR)/interface/*.h
	$(CXX) -o $@ $(CXXFLAGS) $< $(LIBS) -L$(LIBDIR) -l$(LIBNAME)

$(SRCDIR)/$(PKG)/obj/%.$(OBJ_EXT): $(SRCDIR)/$(PKG)/src/%.$(SRC_EXT) $(SRCDIR)/$(PKG)/interface/%.h
	@echo "----->Compiling object: " $@
	$(CXX) $(CXXFLAGS) -fPIC -c $<  -o $@
	@echo ""

$(SRCDIR)/$(PKG)/obj/lib%.so: $(filter %,$(OBJS))
	@echo "----->Producing shared lib: " $@
	$(LD) $(LDFLAGS) -o $@ $<
	@echo ""
	
lib: $(SRCDIR)/$(PKG)/obj/lib$(PKG).so

# info:
# 	@echo "LIBS: " $(LIBS)
# 	@echo "CXXFLAGS: " $(CXXFLAGS)
# 	@echo "Source files: " $(SRCS) 
# 	@echo "Object files: " $(OBJS)
# 	@echo "Executables:  " $(TARGETS)

clean:
	rm -rf $(OBJS) $(SRCDIR)/$(PKG)/obj/lib$(PKG).so $(BINS)
