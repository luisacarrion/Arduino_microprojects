/*========================================================*/
/*
  Micro project 5:
  Song played: For Elise (http://www.forelise.com/media/for_elise_sheet_music.pdf)
*/
/*========================================================*/


#include <avr/delay.h>

/*------- Hardware configuration -------*/
const int  speaker_pin = 2; 

// Half period of the notes
const int _C2 = 3822;
const int _C2s = 3608;
const int _D2 = 3405;
const int _D2s = 3214;
const int _E2 = 3034;
const int _F2 = 2864;
const int _F2s = 2703;
const int _G2 = 2551;
const int _G2s = 2408;
const int _A2 = 2273;
const int _A2s = 2145;
const int _B2 = 2015;
const int _C3 = 1911;
const int _C3s = 1804;
const int _D3 = 1703;
const int _D3s = 1607;
const int _E3 = 1517;
const int _F3 = 1432;
const int _F3s = 1351;
const int _G3 = 1276;
const int _G3s = 1204;
const int _A3 = 1136;
const int _A3s = 1073;
const int _B3 = 1012;
const int __ = 0;

const int total_notes = 41;
int current_note = 0;
long time_started = 0;
boolean start_new_time = true;

int melody[] = {   
  _E3, _D3s, _E3, _D3s, _E3, _B2, _D3, _C3, _A2, __,
  _C2, _E2, _A2, _B2, __, _E2, _G2s, _B2, _C3, __,
  _E2, _E3, _D3s, _E3, _D3s, _E3, _B2, _D3, _C3, _A2, __,
  _C2, _E2, _A2, _B2, __, _E2, _C3, _B2, _A2, __
//  B2, C3, D3, E3, G2, F2, E3, D3, E3, E3, D3, C3, E3, D3, C3, E3,
//  E3, D3s, E3, D3s, E3, E3, D3, C3, A2, 
//  C3, E3, A2, B2, E3, A2, B2, C3,
//  E3, D3s, E3, D3s, E3, B2, D3, C3, A2, 
//  C3, E3, A2, B2, E3, C3, B2, A2
};

int melody_duration[]  = { 
  250, 250, 250, 250, 250, 250, 250, 250, 500, 250, 
  250, 250, 250, 500, 250, 250, 250, 250, 500, 250,
  250, 250, 250, 250, 250, 250, 250, 250, 250, 500, 250,
  250, 250, 250, 500, 250, 250, 250, 250, 500, 500
};



/* Initializization code (run once via call from Arduino framework) */
void setup() {
  // open the serial port at 9600 bps:
  //Serial.begin(9600); 
  
  // establish direction of pins we are using for LEDs 
  pinMode(speaker_pin, OUTPUT); 

}

/* Main routine (called repeated by from the Arduino framework) */
void loop() {
 
  if ( start_new_time ) {
    time_started = millis();
    start_new_time = false;
  }
  
  if ( melody[current_note] != 0 ) {
    digitalWrite(speaker_pin, HIGH);
    _delay_us( melody[current_note] );
    digitalWrite(speaker_pin, LOW);
    _delay_us( melody[current_note] );
  }

  if ( ( millis() - time_started ) >= melody_duration[current_note] ) {
    current_note++;
    start_new_time = true;
    if ( current_note == total_notes ) {
      current_note = 0;
    }
  }
 
}  // end loop()

