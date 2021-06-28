
/* To do

Map the resistor divider to ADC input gain for 0 - 10v then map to 0 - 300v etc...
wifi setup and code
vacuum lookup table
PID test and setup


*/

#define DEBUG

 

enum State {
  IDLE,
  VACUUM,
  HIGHVOLTAGE,
  COOLDOWN,
  ALARM
} state;

void setup() {
  
  buttons.setup();
  adc.setup();
  motor.setup();
  oled.setup();
  rtc.setup();
  sd.setup();
  temp.setup();
  wifi.setup();
  
  
  
 
  state = IDLE;
}

loop() {
  read inputs (including millis());

  switch(STATE) {
  case IDLE:
    if(some condition) {
      start the arm rotating;
      state = ARM_ROTATING;
    }
    else if(some other condition) {
      start the process of closing the steam
      state = STEAM_CLOSING;
    }
    break;

  case ARM_ROTATING:
    if(theArmStillNeedsToRotateSomeMore()) {
      rotate the arm some more;
      // stay in ARM_ROTATING state
    }
    else {
      begin hord actuation();
      state = HORD_ACTUATION_TIMEOUT;
    }
   break;

   et cetera.

  }
}
