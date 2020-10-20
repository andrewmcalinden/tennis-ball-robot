motorTest: Motor.o MotorTest.o
	g++ -o motorTest Motor.o MotorTest.o -lwiringPi

Motor.o: ./Motor/Motor.cpp ./Motor/Motor.h
	g++ -c ./Motor/Motor.cpp -lwiringPi

MotorTest.o: ./Motor/MotorTest.cpp ./Motor/Motor.h
	g++ -c ./Motor/MotorTest.cpp -lwiringPi

odomTest: BETAEncoders.o odometry.o
	g++ -o odomTest odomTest.cpp BETAEncoders.o odometry.o

BETAEncoders.o: ./BETA/encoderL.cpp ./BETA/encoderL.cpp ./BETA/encoderL.h ./BETA/encoderL.h
	g++ -c ./BETA/encoderR.cpp ./BETA/encoderL.cpp -lwiringPi

odometry.o: ./odometry/odometry.cpp ./odometry/vector.cpp ./BETA/odometry.h ./BETA/vector.h
	g++ -c ./odometry/odometry.cpp ./odometry/vector.cpp


clean:
	rm *.o motorTest