//String incomingByte = ""; // for incoming serial data
int data = 345;
char userInput;

void setup() {
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
  
}

void loop() {
  if (Serial.available() > 0){
    
  userInput = Serial.read();
  
    if (userInput == 'g'){
      Serial.println(data);
      data++;
    }
  
    
  }
}
