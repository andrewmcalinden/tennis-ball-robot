INCLUDES := -I/usr/include -I~/wiringPi/wiringPi/
LIBRARIES := -L/usr/lib

NAME := Max1113_spi

LIBS := -L./ -l$(NAME)  -L/usr/local/lib  -lwiringPi 
# for timing measurement
LIBS += -lrt
CXX := g++
EXEC := test_max1113

all: lib $(EXEC)

lib: lib$(NAME).a

$(EXEC):  $(EXEC).o lib$(NAME).a 
	$(CXX)  $^ -o $@ $(LIBRARIES) $(LIBS)
	echo done, execute:    ./$(EXEC)

lib$(NAME).a: $(NAME).o $(NAME).h
	ar -cvq  $@ $(NAME).o

%.o: %.c 
	$(CC) -c  $< $(CFLAGS) 
	echo end of compilation of  $<

clean:
	rm -rf *.o *.a $(EXEC)

