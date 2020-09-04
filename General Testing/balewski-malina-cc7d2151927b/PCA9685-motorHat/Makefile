PATH_SERVOS=/home/pi/malina/PCA9685-servo16
RPI_LIBS= -L$(PATH_SERVOS) -lPCA9685_pwm 

CFLAGS := -Wall
CFLAGS +=   -I$(PATH_SERVOS)


NAME := PCA9685_motorHat

THISLIB := -L./ -l$(NAME)

CXX := g++

RM := rm -rf
EXEC := DCMotorTest


all: lib $(EXEC)
lib: lib$(NAME).a

$(EXEC):  $(EXEC).o lib$(NAME).a
	$(CXX)  $^ -o $@  $(THISLIB)  $(RPI_LIBS)  
	echo done, execute:    ./$(EXEC)

lib$(NAME).a: $(NAME).o 
	ar rul  $@ $(NAME).o

%.o: %.cpp 
	$(CC)  $(CFLAGS) -c  $< 
	echo end of compilation of  $<

clean:
	$(RM) *.o *.a $(EXEC)

