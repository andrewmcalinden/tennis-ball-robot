motorTest: Motor.o MotorTest.o
	g++ -o test Motor.o MotorTest.o -lwiringPi

Motor.o: Motor.cpp Motor.h
	g++ -c Motor.cpp -lwiringPi

MotorTest.o: MotorTest.cpp Motor.h
	g++ -c MotorTest.cpp -lwiringPi

clean:
	rm *.o motorTest