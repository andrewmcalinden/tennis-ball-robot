NAME := PCA9685_pwm
THISLIB := -L./ -l$(NAME)

CFLAGS := -Wall
CXX := g++

RM := rm -rf
EXEC := test_servo

all: lib $(EXEC)

lib: lib$(NAME).a

$(EXEC):  $(EXEC).o lib$(NAME).a
	$(CXX)  $^ -o $@  $(THISLIB)
	echo done, execute:    ./$(EXEC)


lib$(NAME).a: $(NAME).o 
	ar rul  $@ $(NAME).o

%.o: %.cpp 
	$(CXX) -c  $< $(CFLAGS) 
	echo end of compilation of  $<

clean:
	$(RM) *.o *.a $(EXEC)

