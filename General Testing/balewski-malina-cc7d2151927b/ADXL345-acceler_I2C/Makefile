INCLUDES := -I/usr/include
LIBRARIES := -L/usr/lib
SOURCES=ADXL345v2.cpp ADXL345.cpp
HEADRES=$(SOURCES:.cpp=.h)
OBJECTS=$(SOURCES:.cpp=.o)

NAME := ADXL345

LIBS := -L./ -l$(NAME)

CXX := g++

RM := rm -rf
EXEC := test_ADXL345

all:   $(OBJECTS)  $(EXEC) lib$(NAME).a

$(EXEC):  $(EXEC).o lib$(NAME).a
	$(CXX)  $^ -o $@ $(LIBRARIES) $(LIBS)
	echo done, execute:    sudo ./$(EXEC)

lib$(NAME).a: $(OBJECTS) $(HEADRES) 
	ar -cvq  $@ $(OBJECTS)


.cpp.o: $<.h
	echo JM: compile $<
	$(CXX) $(CFLAGS) $< -o $@  $(INCLUDES) -c
	echo JM: end of compilation of  $<

clean:
	$(RM) *.o *.a* $(EXEC) 

