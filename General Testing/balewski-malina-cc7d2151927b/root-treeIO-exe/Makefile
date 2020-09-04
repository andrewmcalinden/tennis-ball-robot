
HDRS     = JbToy6DGen.h  LinReg_Bevington_Pebay.h Toy6DEvent.h  Jb6DRegress.h
SRCS     = JbToy6DGen.cxx LinReg_Bevington_Pebay.cxx  Jb6DRegress.cxx

CXX    = g++
LD     = g++
AR     = ar rul

DEBUG  =-g -O 
DEFINES=
#

OBJS   = $(notdir $(patsubst %.cxx,%.o,$(SRCS)))

# -shared
# disable this 2 for RPi
# LDFLAGS  = -m64
#CFLAGS   = -m64 -Wall $(DEBUG) $(DEFINES)  $(INCL)
CFLAGS   =  -Wall $(DEBUG) $(DEFINES)  $(INCL)
ROOT_LIB  = `root-config --libs`
ROOT_INC  = -I `root-config --incdir`


all: myGen myReco

myReco: myReco.o $(OBJS) 
	$(LD) $(LDFLAGS) -o $@  $^  -l m  -l Minuit $(ROOT_LIB)


myGen: myGen.o $(OBJS)
	$(LD) $(LDFLAGS) -o $@  $^  -l m  -l Minuit $(ROOT_LIB)


clean:
	-rm -f *.o $(LINK)  myReco myGen .depend


depend .depend : $(SRCS) 
	$(CXX) -M $(CFLAGS)  $(ROOT_INC) $^ > ./.depend


%.o: %.cxx
	$(CXX) $(CFLAGS)  $(ROOT_INC) -c $< -o $@


#
-include .depend
