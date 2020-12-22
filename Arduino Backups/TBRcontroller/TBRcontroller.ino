const int xPin = A0;
const int yPin = A1;
const byte switchPin = 2;
const int right = 9;
const int left = 3;
const int collector = 5;

double leftPower = 0;
double rightPower = 0;
volatile bool collectOn = false;

volatile int counter = 0;

double superMap(double x, double in_min, double in_max, double out_min, double out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

double updateJoy(int pin){
  if(superMap(analogRead(pin),0,1024,1,-1)>-.03&&superMap(analogRead(pin),0,1024,1,-1)<.03){
    return 0.0;
  }
  else{
    return superMap(analogRead(pin),0,1024,-.9,.9);
  }
}
void updatePowers(){
  //LEFT
  double leftAxes = updateJoy(yPin) + updateJoy(xPin)/2; //1.35
  
  if (leftAxes>=.9) //left
    leftPower = .9;
    
  else if (leftAxes<=-.9) //left
    leftPower = -.9;
    
  else
    leftPower = leftAxes;
  
  //RIGHT
  double rightAxes = updateJoy(yPin) - updateJoy(xPin)/2; //.45
  
  if (rightAxes>=.9) //right
    rightPower = .9;

  else if (rightAxes<=-.9)//right
    rightPower = -.9;
    
  else
    rightPower = rightAxes;
    
  rightPower = ((rightPower+1)/2)*255;
  leftPower = ((leftPower+1)/2)*255;
}
void collectorTrigger(){
  if (collectOn){
    digitalWrite(collector, LOW);
    collectOn = false;
    //Serial.print("WORKSON");
  }
  else{
    digitalWrite(collector, HIGH);
    collectOn = true;
    //Serial.print("WORKSOFF");
  }
  
  //while(digitalRead(switchPin) == 1){}
}

void setup() {
  // put your setup code here, to run once:
pinMode(xPin, INPUT);
pinMode(yPin, INPUT);
pinMode(switchPin, INPUT_PULLUP);
pinMode(left, OUTPUT);
pinMode(right, OUTPUT);
attachInterrupt(0,&collectorTrigger, RISING);

//Serial.begin(115200);

}

void loop() {
  updatePowers();
  
  analogWrite(right, (int)rightPower);
  analogWrite(left, (int)leftPower);
  
  
}
