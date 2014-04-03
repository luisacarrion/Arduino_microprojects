/*========================================================*/
/*
  Micro project 6:
  Servo motor: The code for the project was obtain in the slides provided by the professor.
*/
/*========================================================*/

/*------- Hardware configuration -------*/
const int potPin = A4;
const int  servoPin = 8; 

void servoPulse(int angle1024) {
	digitalWrite(servoPin, HIGH);
	delayMicroseconds(600 + (angle1024 << 1));
	digitalWrite(servoPin, LOW);
	delay(18);
}

/* Initializization code (run once via call from Arduino framework) */
void setup() {
  // open the serial port at 9600 bps:
  //Serial.begin(9600); 
  
  pinMode(potPin, INPUT); 
  pinMode(servoPin, OUTPUT); 

}

/* Main routine (called repeated by from the Arduino framework) */
void loop() {

  servoPulse(analogRead(potPin));
 
}  // end loop()

