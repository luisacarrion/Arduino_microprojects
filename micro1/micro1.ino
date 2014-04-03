/*========================================================*/
/*
  Micro project 1:
  The code from candle1.txt provided by the professor was taken as model for this project.
*/
/*========================================================*/

/*------- Hardware configuration -------*/
const int  pin1 = 2;         
const int  pin2 = 3;         
const int  pin3 = 4;         
const byte pin4 = 5;        

/* Initializization code (run once via call from Arduino framework) */
void setup() {
  // establish direction of pins we are using for LEDs 
  pinMode(pin1, OUTPUT); 
  pinMode(pin2, OUTPUT); 
  pinMode(pin3, OUTPUT); 
  pinMode(pin4, OUTPUT); 
  
  // Turn on all pins at once so we know they are alive and hooked up right
  digitalWrite(pin1, HIGH);
  digitalWrite(pin2, HIGH);
  digitalWrite(pin3, HIGH);
  digitalWrite(pin4, HIGH);
  delay(250);
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, LOW);
  digitalWrite(pin3, LOW);
  digitalWrite(pin4, LOW);  
}

/* Main routine (called repeated by from the Arduino framework) */
void loop() {
 
 //Turn the first LED on for 2 seconds, 
 digitalWrite(pin1, HIGH); delay(2000); digitalWrite(pin1, LOW);
 
 //then the second for 1 second, 
 digitalWrite(pin2, HIGH); delay(1000); digitalWrite(pin2, LOW);
 
 //the third for a ½ second, 
 digitalWrite(pin3, HIGH); delay(500); digitalWrite(pin3, LOW);
 
 //and then the fourth for a ¼ second. 
 digitalWrite(pin4, HIGH); delay(250); digitalWrite(pin4, LOW);
 
 delay(250);
 
 //Then flash the four in some pattern of your choosing. Wait ½ second, and then repeat
 digitalWrite(pin4, HIGH); delay(125); digitalWrite(pin4, LOW);
 digitalWrite(pin3, HIGH); delay(125); digitalWrite(pin3, LOW); 
 digitalWrite(pin2, HIGH); delay(125); digitalWrite(pin2, LOW);
 digitalWrite(pin1, HIGH); delay(125); digitalWrite(pin1, LOW);
 
 digitalWrite(pin1, HIGH); delay(70); digitalWrite(pin1, LOW);
 digitalWrite(pin2, HIGH); delay(70); digitalWrite(pin2, LOW);
 digitalWrite(pin3, HIGH); delay(70); digitalWrite(pin3, LOW);
 digitalWrite(pin4, HIGH); delay(70); digitalWrite(pin4, LOW);
 
 digitalWrite(pin4, HIGH); delay(35); digitalWrite(pin4, LOW);
 digitalWrite(pin3, HIGH); delay(35); digitalWrite(pin3, LOW); 
 digitalWrite(pin2, HIGH); delay(35); digitalWrite(pin2, LOW);
 digitalWrite(pin1, HIGH); delay(35); digitalWrite(pin1, LOW);

 digitalWrite(pin1, HIGH); delay(35); digitalWrite(pin1, LOW);
 digitalWrite(pin2, HIGH); delay(35); digitalWrite(pin2, LOW);
 digitalWrite(pin3, HIGH); delay(35); digitalWrite(pin3, LOW);
 digitalWrite(pin4, HIGH); delay(35); digitalWrite(pin4, LOW);

 digitalWrite(pin4, HIGH); delay(35); digitalWrite(pin4, LOW);
 digitalWrite(pin3, HIGH); delay(35); digitalWrite(pin3, LOW); 
 digitalWrite(pin2, HIGH); delay(35); digitalWrite(pin2, LOW);
 digitalWrite(pin1, HIGH); delay(35); digitalWrite(pin1, LOW);

 digitalWrite(pin1, HIGH); delay(35); digitalWrite(pin1, LOW);
 digitalWrite(pin2, HIGH); delay(35); digitalWrite(pin2, LOW);
 digitalWrite(pin3, HIGH); delay(35); digitalWrite(pin3, LOW);
 digitalWrite(pin4, HIGH); delay(35); digitalWrite(pin4, LOW);

 digitalWrite(pin4, HIGH); delay(35); digitalWrite(pin4, LOW);
 digitalWrite(pin3, HIGH); delay(35); digitalWrite(pin3, LOW); 
 digitalWrite(pin2, HIGH); delay(35); digitalWrite(pin2, LOW);
 digitalWrite(pin1, HIGH); delay(35); digitalWrite(pin1, LOW);

 digitalWrite(pin1, HIGH); delay(35); digitalWrite(pin1, LOW);
 digitalWrite(pin2, HIGH); delay(35); digitalWrite(pin2, LOW);
 digitalWrite(pin3, HIGH); delay(35); digitalWrite(pin3, LOW);
 digitalWrite(pin4, HIGH); delay(35); digitalWrite(pin4, LOW);

 
 int cycles = 20;
 for (int cnt = 0; cnt < cycles ; cnt++) {
   digitalWrite(pin1, HIGH); delay(35); 
   digitalWrite(pin1, LOW); delay(17);

   digitalWrite(pin2, HIGH); delay(16); 
   digitalWrite(pin2, LOW); delay(8);

   digitalWrite(pin3, HIGH); delay(8); 
   digitalWrite(pin3, LOW); delay(4);

   digitalWrite(pin4, HIGH); delay(2); 
   digitalWrite(pin4, LOW); delay(1);

   
 } // end for
 
}  // end loop()

