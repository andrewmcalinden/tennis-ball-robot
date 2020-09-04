# This Makefile should properly handle .h dependencise, even in sub-dirs
# list of sources
SRCS := $(wildcard *.cc) subJ/kot.cc

# List my OBJ
OBJS := $(patsubst %.cc,%.o,$(SRCS))

# list of execs ( both are identical in this example)
BINS := doIt1 doIt2

# needed for cleaning & dependencies
OBJSM =$(OBJS) + $(patsubst %,%.o,$(BINS)) 

# add -lstdc++ for  vector<int> v;
LDFLAGS :=  -L/usr/local/lib -lstdc++
CFLAGS_INC :=  -I/usr/include -IsubJ
CFLAGS := -g -Wall $(CFLAGS_INC)

# link all exec
all : $(BINS)

doIt1: $(OBJS)
	gcc $(OBJS)  $(LDFLAGS) -o $@
	@echo "Jan-DONE exec    ./$@"	

doIt2: $(OBJS)
	@touch ./$@
	@echo JanDone:  NOT implemented    ./$@	

# pull in dependency info for *existing* .o files
-include $(OBJSM:.o=.d)

# compile and generate dependency info
%.o: %.cc
	@# Compile the object file
	@echo " C++ : " $< " => " $@
	gcc -c $(CFLAGS) $*.cc -o $*.o
	gcc -MM $(CFLAGS) $*.cc > $*.d

# remove compilation products
clean:
	rm -f $(BINS) $(OBJSM) $(OBJSM:.o=.d)
