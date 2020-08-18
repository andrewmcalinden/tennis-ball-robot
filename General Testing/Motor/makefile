test: Motor.o MotorTest.o
	g++ -o test Motor.o MotorTest.o

Motor.o: Motor.cpp Motor.h
	g++ -c Motor.cpp

MotorTest.o: MotorTest.cpp Motor.h
	g++ -c MotorTest.cpp

clean:
	rm *.o test