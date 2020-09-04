INCLUDES := -I/usr/include
LIBRARIES := -L/usr/lib

#.... add wiringPi libraries
LIBRARIES +=-L/usr/local/lib -lwiringPi


LIBNAME  = util_cpp
HDRS     = $(wildcard Buzz*.h)
SRCS     = $(wildcard Buzz*.cpp)


OBJS   = $(notdir $(patsubst %.cpp,%.o,$(SRCS)))


LIBRARIES += -L./ -l$(LIBNAME)

CXX := g++

RM := rm -rf
EXEC := test_buzz

all: lib $(EXEC)

lib: lib$(LIBNAME).a

$(EXEC):  $(EXEC).o lib$(LIBNAME).a
	$(CXX)  $^ -o $@ $(LIBRARIES) 
	echo done, execute:    sudo ./$(EXEC)

lib$(LIBNAME).a: $(OBJS) $(HDRS)
	ar -cvq  $@ $(OBJS)

%.o: %.c 
	$(CC) -c  $< $(CFLAGS)   $(INCLUDES)
	echo end of compilation of  $<

clean:
	$(RM) *.o *.a* $(EXEC)

