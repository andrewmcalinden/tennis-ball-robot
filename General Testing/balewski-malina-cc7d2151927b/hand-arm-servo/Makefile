INCLUDES := -I/usr/include
LIBRARIES := -L/usr/lib

EXEC := main-hand-arm-2servo


#....... add PCA9685 servo-16 board
path_ADXL345 := ../PCA9685-servo16/
LIBRARIES += -L $(path_ADXL345)   -lPCA9685
INCLUDES  += -I $(path_ADXL345)

#....... add util_cpp
path_UTIL_CPP := ../util_cpp/
LIBRARIES += -L $(path_UTIL_CPP)   -lutil_cpp
INCLUDES  += -I $(path_UTIL_CPP)

#.... add wiringPi libraries
LIBRARIES +=-L/usr/local/lib -lwiringPi


CXX := g++

RM := rm -rf

$(EXEC):  $(EXEC).o 
	echo CCFL=$(CFLAGS)
	$(CXX)   $^ -o $@ $(LIBRARIES) 
	echo done, execute:    sudo ./$(EXEC)

%.o: %.cpp
	$(CXX) -c  $<  $(INCLUDES)
	echo end of compilation of  $<

clean:
	$(RM) *.o *.a* $(EXEC)


