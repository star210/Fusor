
/* To do

vacuum lookup table
PID test with dummy load
Decide when and what to write to OLED 
handle alarmstate 
print sensors and temps to serial every x seconds

*/

bool safetyTriggered = 0;           //Removal of plinth cover vacuum ok but no HV
bool alarmState = 0;
 
enum State {
  IDLE,
  PUMP_DOWN,
  HIGH_VOLTAGE,
  COOLDOWN,
  ALARM
} state;

void setup() {

 
  buttons.setup();
  adc.setup();
  variac.setup();
  oled.setup();
  rtc.setup();
  sd.setup();
  temp.setup();
  
  state = IDLE;
}

loop() {

if (alarmState){
  variacRelayState = 0; // turn off power
  pumpRelayState = 0;   // turn off vacuum pump
}


  
  read inputs (including millis());

  switch(STATE) {
  case IDLE:
    if(pump started) {
      state = PUMP_DOWN;
    }
    break;

  case PUMP_DOWN:
  if (!pumpRelayState){
    start pump timeout
  }
  if (pump timer < PUMP_TIMEOUT){
    if(current pressure < MIN_PRESSURE){
      
    }
    }
    else {
      begin hord actuation();
      state = HORD_ACTUATION_TIMEOUT;
    }
   break;

case PUMP_DOWN:
  if (!pumpRelayState){
    start pump timeout
  }
  if (pump timer < PUMP_TIMEOUT){
    if(current pressure < MIN_PRESSURE){
      
    }
    }
    else {
      begin hord actuation();
      state = HORD_ACTUATION_TIMEOUT;
    }
   break;

  }
}
