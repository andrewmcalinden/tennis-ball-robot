LIBNAME  = WtreeCode
HDRS     = $(wildcard W*.h)
SRCS     = $(wildcard W*.cxx) 

# on linux
#CXX    = g++
#LD     = g++
#on mac
CXX    = c++
LD     = c++
AR     = ar rul

DEBUG  =-g -O 
DEFINES=

ROOTCFLAGS    = $(shell root-config --cflags) 
ROOTLIBS      = $(shell root-config --libs) 

# Mac : take this one out: -lNew

#
LINK   = LinkDef.h
DICT   = Dict_$(LIBNAME)
SRCS  += $(DICT).cxx
OBJS   = $(notdir $(patsubst %.cxx,%.o,$(SRCS))) 

#
CFLAGS   = -Wall $(DEBUG) $(DEFINES) -fPIC $(ROOTCFLAGS)
CXXFLAGS = $(CFLAGS)
LDFLAGS  = -shared 

all:	$(LIBNAME)
#	-rm  $(LINK) $(DICT).*	

# note, for MacOS you need to specify all root .so when building the .so for your project
$(LIBNAME): $(OBJS)
	$(CXX) $(LDFLAGS) $^ $(ROOTLIBS)  -o lib$(LIBNAME).so
	$(AR)  lib$(LIBNAME).a $^


clean:
	-rm -f *.o $(LINK) $(DICT).* lib$(LIBNAME).* toyEve.tree.root


# ROOT STUFF
$(DICT).cxx: $(HDRS) $(LINK)
	rootcint -f $@ -c $^

$(LINK):  $(HDRS)
	./mklinkdef.pl $(HDRS) > $(LINK)


%.o: %.cxx
	$(CXX) $(CXXFLAGS) -c $< -o $@

