/*========================================================*/
/*
  Micro project 1:
  The code from candle1.txt provided by the professor was taken as model for this project.
*/
/*========================================================*/

/*------- Hardware configuration -------*/
const int  switch_up = 6;
const int  switch_down = 7;

int  switch_up_state = 0;
int  switch_down_state = 0;
int  pin1 = 2;         
int  pin2 = 3;         
int  pin3 = 4;         
int  pin4 = 5;     

/* Initializization code (run once via call from Arduino framework) */
void setup() {
  // establish direction of pins we are using for LEDs 
  pinMode(pin1, OUTPUT); 
  pinMode(pin2, OUTPUT); 
  pinMode(pin3, OUTPUT); 
  pinMode(pin4, OUTPUT); 
  pinMode(switch_up, INPUT);
  pinMode(switch_down, INPUT);
  
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
 
 switch_up_state = digitalRead(switch_up);
 
 switch_down_state = digitalRead(switch_down);
 
 if (switch_up_state == HIGH) {
   switch_down_state = LOW;  
   pin1 = 2;         
   pin2 = 3;         
   pin3 = 4;         
   pin4 = 5;        

 }
 else if (switch_down_state == HIGH) {
   switch_up_state = LOW;
   pin1 = 5;         
   pin2 = 4;         
   pin3 = 3;         
   pin4 = 2;           
 }
 
 digitalWrite(pin1, HIGH); delay(70); digitalWrite(pin1, LOW);
 digitalWrite(pin2, HIGH); delay(70); digitalWrite(pin2, LOW);
 digitalWrite(pin3, HIGH); delay(70); digitalWrite(pin3, LOW);
 digitalWrite(pin4, HIGH); delay(70); digitalWrite(pin4, LOW);
 
// digitalWrite(pin1, HIGH); delay(35); digitalWrite(pin1, LOW);
// digitalWrite(pin2, HIGH); delay(35); digitalWrite(pin2, LOW);
// digitalWrite(pin3, HIGH); delay(35); digitalWrite(pin3, LOW);
// digitalWrite(pin4, HIGH); delay(35); digitalWrite(pin4, LOW);
//
// digitalWrite(pin1, HIGH); delay(35); digitalWrite(pin1, LOW);
// digitalWrite(pin2, HIGH); delay(35); digitalWrite(pin2, LOW);
// digitalWrite(pin3, HIGH); delay(35); digitalWrite(pin3, LOW);
// digitalWrite(pin4, HIGH); delay(35); digitalWrite(pin4, LOW);
//
// digitalWrite(pin1, HIGH); delay(35); digitalWrite(pin1, LOW);
// digitalWrite(pin2, HIGH); delay(35); digitalWrite(pin2, LOW);
// digitalWrite(pin3, HIGH); delay(35); digitalWrite(pin3, LOW);
// digitalWrite(pin4, HIGH); delay(35); digitalWrite(pin4, LOW);

 
}  // end loop()

