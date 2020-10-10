motorTest: Motor.o MotorTest.o
	g++ -o motorTest Motor.o MotorTest.o -lwiringPi

Motor.o: ./Motor/Motor.cpp ./Motor/Motor.h
	g++ -c ./Motor/Motor.cpp -lwiringPi

MotorTest.o: ./Motor/MotorTest.cpp ./Motor/Motor.h
	g++ -c ./Motor/MotorTest.cpp -lwiringPi

clean:
	rm *.o motorTest