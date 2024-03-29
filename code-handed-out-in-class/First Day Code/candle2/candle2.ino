/*========================================================*/
/*
  LED Candle Demo v0.2b (Full Version)
  by Scott Hudson, HCI Institute, CMU 1/10
  
  This program provides a demo of basic techniques (push button input and
  driving some LEDs) in the form of a simulated candle created with an RGB
  LED. 
  
  Hardware
  This code assumes a push button (normally open) switch and three LEDs or
  a combined RBG LED.  The switch and each of the LEDs should be attached to
  a separate digital I/O pin (as indicated in the constants below).  The LEDs 
  are assumed to be connected as common cathode attached to ground and should should
  each have a current limiting resistor (probably in the 200-500 ohm range for 5v 
  hardware).  The switch is assumed to have a pull-down resistor (so is high when 
  depressed and low when released).
  
  Operation
  Candle is initially off.  When you press the button it turns on and flickers 
  with a default yellow-white color.  Each time you subsequently press the button 
  it cycles to a new base color, then eventually back to being off.  Nothing in 
  particular is done to save power when the candle is off.
  
  Revisions
  1/10  Initial version v0.1a
  1/10  Split into 3 progressively more complete versions v0.2a
  1/12  Small tweek to update for wierdness in handling typedefs in later IDE versions  v0.2b
*/
/*========================================================*/

/*------- Hardware configuration -------*/
const int  switchPin = 5;        // pin with switch attached
const int  redPin = 2;           // pin red LED is attached to 
const int  greenPin = 4;         // pin for green LED
const int  bluePin = 3;          // pin for blue LED
const byte debugPin = 13;        // pin that we put debug output on (set to 255 to disable)
                                 // (most Arduino's have a built in LED on pin 13...)

/*------- Data structures for system state -------*/      

/* Structure to track and debounce the state of a push button switch */
typedef struct switchTracker {
  int lastReading;       // last raw value read
  long lastChangeTime;   // last time the raw value changed
  byte pin;              // the pin this is tracking changes on
  byte switchState;      // debounced state of the switch
} switchTrack;

// Note (v0.2b): due to some wierdness in the ordering of generated code, typdefs as above no longer
// fully work unless they are in .h files.  In particular, you can't do the above and then declare 
// a function parameter using the type name.  Rather than introduce an additional file, we have just used
// the raw struct type in parameter declarations as a small work around.

/* Fill in a switchTrack structure to start tracking/debouncing a switch
   on the given pin.
*/
void initSwitchTrack(struct switchTracker &sw, int swPin) {  
  pinMode(swPin, INPUT);
  sw.lastReading = digitalRead(swPin);
  sw.lastChangeTime = millis();
  sw.pin = swPin;
  sw.switchState = sw.lastReading;
}

// Structure representing the color and duration of one flicker segment
typedef struct flickerVal {
  byte redV, greenV, blueV;   // 0..255 to represent 0%-100% on time (hence percieved intensity)
  unsigned int flickDur;      // duration in msec
} flickerValues;

/*------- Global system state -------*/
const byte FLAME_OFF = 0;    // constant indicating candle is off
const byte MAX_COLOR = 5;    // index of largest flame color
byte flameMode = FLAME_OFF;  // should be set to FLAME_OFF or a flame color 1..MAX_COLOR
switchTrack switchInput;     // tracking / debounce information for our switch

/*-------------------------------------------*/
/* Flash the debug LED for the given time in msec.  The LED is on for flashMSec then held
   off for the same amount of time (so this routine takes 2*flashMSec total).
 */
void dbgFlash(int flashMSec) {
  if (debugPin != 255) {
    digitalWrite(debugPin,HIGH); delay(flashMSec); 
    digitalWrite(debugPin,LOW); delay(flashMSec);
  }
}
  
/*-------------------------------------------*/
/* Initializization code (run once via call from Arduino framework) */
void setup() {
  // establish direction of pins we are using for LEDs 
  pinMode(redPin, OUTPUT); pinMode(greenPin, OUTPUT); pinMode(bluePin, OUTPUT);
  
  // set up debounce tracker on our switch input pin (sets mode to INPUT)
  initSwitchTrack(switchInput, switchPin);
  
  // drive the RGB LEDs in sequence so we know they are alive and hooked up right
  if (debugPin != 255) {
    pinMode(debugPin, OUTPUT);
    digitalWrite(debugPin,HIGH); delay(250); digitalWrite(debugPin,LOW);
    digitalWrite(redPin,HIGH); delay(250); digitalWrite(redPin,LOW);
    digitalWrite(greenPin,HIGH); delay(250); digitalWrite(greenPin,LOW);
    digitalWrite(bluePin,HIGH); delay(250); digitalWrite(bluePin,LOW);
  }
}

/* Main routine (called repeated by from the Arduino framework) */
void loop() {
  // do a flicker segment
  flick();
}

/*-------------------------------------------*/
/* Using a time based debounce, test whether a switch should be considered to have 
   changed state since the last call to this routine for the switch, and track the 
   current state of the switch in the given switch tracking structure (sw).  The switch 
   will be consided to be in a new state only after it has held that state for debounceTime msec 
   or longer.  sw.switchState will be set to 1 when the switch should be considered pressed 
   and 0 when it should be considered released.  This routine will return true when the 
   switch is in a new state compared to the last call to this routine, false otherwise.
   
   Note: this routine must be called frequently to operate correctly.
   Note: this code is here to make the demo a little more stand alone (nothing to import),
         but in other cases you might want to consider using the code from Bounce.h instead.
*/
boolean switchChange(struct switchTracker &sw) { 
  // switch must stay stable this long (in msec) to register
  const long debounceTime = 100;   
  
  // default to no change until we find out otherwise
  boolean result = false; 
  
  // get the current raw reading from the switch
 int reading = digitalRead(sw.pin);

  // if the raw reading has changed (by noise or actual press/release) reset change time to now
  if (reading != sw.lastReading) sw.lastChangeTime = millis();
  sw.lastReading = reading;
  
  // if time since the last change is longer than the required dwell
  if ((millis() - sw.lastChangeTime) > debounceTime) {
    // note whether we are changing
    result = (reading != sw.switchState);
    // in any case the value has been stable and so the reported state 
    // should now match the current raw reading
    sw.switchState = reading;
  }
  return result;
}

/*-------------------------------------------*/
/* Routine to pick pick a random color in some range (depending on what the current
   flameMode is) and a duration to hold that color (again depending on what the current
   flameMode is).  
*/ 
void pickColor(struct flickerVal &result) {
    switch (flameMode) {
    default: // if we find a flame mode we don't understand here, force us to off
    case FLAME_OFF:
      flameMode = FLAME_OFF;
      result.redV = result.greenV = result.blueV = 0;
      result.flickDur = 100;
      return;
      
    case 1: /* yellow-white */
      result.redV = result.greenV = (byte)random(127,255);  // equal red and green gives yellow
      result.blueV = (byte)random(0,64); // add in some blue to make it (randomly) more towards white
      result.flickDur = (unsigned int)random(50,100);   // duration in msec
      return;
    
    case 2: /* bluish */
      result.redV = result.greenV = (byte)random(64,64);
      result.blueV = (byte)random(127,255);
      result.flickDur = (unsigned int)random(50,100);
      return;
      
    case 3: /* pure yellow */
      result.redV = result.greenV = (byte)random(127,255);  // equal red and green gives yellow
      result.blueV = 0;
      result.flickDur = (unsigned int)random(50,100);
      return;
    
    case 4: /* fast flickering yellow-white */
      result.redV = result.greenV = (byte)random(127,255);  // equal red and green gives yellow
      result.blueV = (byte)random(0,64); // add in some blue to make it (randomly) more towards white
      result.flickDur = (unsigned int)random(0,10);
      return;
      
    case 5: /* pure red */
      result.redV = random(127,255); 
      result.greenV = result.blueV = 0;
      result.flickDur = (unsigned int)random(50,100);
      return;
  }
}

/*-------------------------------------------*/
/* Routine to do one element of flicker in a randomly chosen color for a randomly chosen
   duration (both picked by pickColor() based on the current flameMode). 
 */
void flick(void) {
  // pick a color and duration based on the flameMode
  flickerValues flk;
  pickColor(flk);
  
  // loop to continue lighting for the selected duration
  unsigned long startTime = millis();
  while (millis() - startTime < flk.flickDur) {
    
    // turn all the non-zero LEDs on
    if (flk.redV != 0) digitalWrite(redPin, HIGH);
    if (flk.greenV != 0) digitalWrite(greenPin, HIGH);
    if (flk.blueV != 0) digitalWrite(bluePin, HIGH);
    
    // count out 255 units of LED intensity.  We will leave each LED on for 
    // some percentage of those as specified by its 0..255 intensity value.
    for (int cnt = 0; cnt < 255; cnt++) {
      // if we are at the setting for a particular color, turn it off
      if (cnt >= flk.redV) digitalWrite(redPin, LOW);
      if (cnt >= flk.greenV) digitalWrite(greenPin, LOW);
      if (cnt >= flk.blueV) digitalWrite(bluePin, LOW);
      
      // see if the switch has been pressed
      if (switchChange(switchInput) && switchInput.switchState == 1 /* pressed */) {
        // move to the next flameMode and bail out of this flicker segment now
        flameMode++;  if (flameMode > MAX_COLOR) flameMode = 0;
        dbgFlash(50);  // debug flash so we know the switch input is working right
        goto done;  
      }
    } // end for
  } // end while
  
  done:
  // turn off all LEDs
  digitalWrite(redPin,LOW);
  digitalWrite(greenPin,LOW);
  digitalWrite(bluePin,LOW);
}


