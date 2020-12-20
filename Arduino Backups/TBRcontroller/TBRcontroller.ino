const int xPin = A0;
const int yPin = A1;
const int collectPin = 2;
const int right = 9;
const int left = 3;
const int collector = 5;

double leftPower = 0;
double rightPower = 0;
bool collectOn = false;

void setup() {
  // put your setup code here, to run once:
pinMode(xPin, INPUT);
pinMode(yPin, INPUT);
pinMode(collectPin, INPUT);
pinMode(left, OUTPUT);
pinMode(right, OUTPUT);
attachInterrupt(digitalPinToInterrupt(collectPin), collectorTrigger, RISING);
Serial.begin(9600);

}

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
    Serial.print("LOW");
    collectOn = false;
  }
  else{
    digitalWrite(collector, HIGH);
    Serial.print("HIGH");
    collectOn = true;
  }
}

void loop() {
  updatePowers();
  delay(10);
  analogWrite(right, (int)rightPower);
  analogWrite(left, (int)leftPower);
}
