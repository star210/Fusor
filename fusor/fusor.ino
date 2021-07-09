
/* To do

  vacuum lookup table
  PID test with dummy load
  serial print rtc timer
  handle voltage up in variac
  when vacuum is above min start voltage up
  hold voltage at max for x amount of time
  then wind down
  cooldown for x amount of time
  repeat

*/

#define INCREASE_TIME 400;

int alarmState = 0;           //Removal of plinth cover vacuum ok but no HV


enum State {
  IDLE,
  VACUUM,
  PLASMA,
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

  unsigned long timeNow = millis() ;

  if (alarmState > 0) {  // If any of the 5 alarms trigger set to alarm state
    state = ALARM;
  }

  switch (STATE) {
    case IDLE:
      if (buttonType == 1) { // Square button pressed
        state = VACUUM;
      }
      break;

    case VACUUM:
      vacuumPump = 1; // Start vacuum pump routine
      if (vacuumPressure < MIN_PRESSURE) {
        state = PLASMA;  //can this be done in vacuum.hpp ?
      }
      break;

    case VOLTAGE_UP:
      unsigned long lastTime;
      variacRelayState = 1; // turn on power to variac
      if (timeNow - lastTime > INCREASE_TIME) {        // increase voltage every 400ms
        lastTime = timeNow;               // update time stamp
        if (setVoltage < MAX_VOLTAGE) {
          setVoltage ++;                   // add one volt to the variac input
        }
        else if (setVoltage = < MAX_VOLTAGE) {

        }
      }
      break;

    case PLASMA:

      break;

    case ALARM:
      variacRelayState = 0; // turn off power
      setVoltage = 0;       // set variac to 0v
      pumpRelayState = 0;   // turn off vacuum pump
      if (buttonType == 1) { // Square button pressed
        Serial.println("Alarm reset");
        alarmState = 0;      // Reset alarm state
        state = PUMP_DOWN;   // Start pumpdown again
        pumpStarted = 0;     // reset pump bool here just incase
      }
      break;
  }
}

void printAlarmState(alarmState) {

}
unsigned long lastAlarmPrint;
if (now - lastAlarmPrint > 1000) {
  if (alarmState == 1) {
    Serial.println("Warning vacuum pump overheated");
  }
  if (alarmState == 2) {
    Serial.println("Warning plasma plate overheated");
  }
  if (alarmState == 3) {
    Serial.println("Warning transformer overheated");
  }
  if (alarmState == 4) {
    Serial.println("Warning cover removed");
  }
  if (alarmState == 5) {
    Serial.println("Vacuum leak detected, check seal");
  }
  lastAlarmPrint = timeNow;  // update timer
}
