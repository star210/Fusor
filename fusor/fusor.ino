
/* To do

wifi setup and code
vacuum lookup table
PID test
Function to write to OLED within main
debug
test oled sensor readout position





*/

#define DEBUG

 

enum State {
  IDLE,
  TEST,
  PUMPDOWN,
  HIGHVOLTAGE,
  COOLDOWN,
  ALARM
} state;

void setup() {

  #if defined(DEBUG)
  Debug.begin(115200);
#else
  client.open(0);
#endif
  
  buttons.setup();
  adc.setup();
  variac.setup();
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
