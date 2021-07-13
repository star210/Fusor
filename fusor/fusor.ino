
/* To do

  vacuum lookup table
  PID test check voltage with dummy load
  temp sensor pin 25 not working...
*/

#define VOLTAGE_STEP_TIME 100;   // smaller is faster ramp speed
#define COOLDOWN_TIME 1000;      // time to cool components after a cycle
#define PLASMA_TIME 1000;        // plasma on time at max voltage

unsigned long plasmaTimer;
unsigned long plasmaTime;
unsigned long cooldownTimer;
unsigned long cooldownTime;
unsigned long lastTime;

bool cooldownStarted = 0;
bool plasmaStarted = 0;

int alarmState = 0;          // alarmState variable


enum State {
  IDLE,
  VACUUM,
  VOLTAGE_UP,
  PLASMA,
  VOLTAGE_DOWN,
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
  readbutton
  if (alarmState > 0) {  // If any of the 5 alarms trigger set to alarm state
    state = ALARM;
  }

  switch (STATE) {
    case IDLE:
      // readbutton here
      if (buttonType == 1) { // Square button pressed
        state = VACUUM;
      }
      break;

    case VACUUM:
      vacuumPump = 1;                                        // Start vacuum pump routine
      if (vacuumPressure < MIN_PRESSURE) {                   // pressure low enough to allow safe plasma with arcing
        state = PLASMA;                                      //can this be done in vacuum.hpp ?
        variacRelayState = 1;                                // turn on power to variac
      }
      break;

    case VOLTAGE_UP:
      if (millis() - lastTime > VOLTAGE_STEP_TIME) {        // increase voltage every 100ms
        if (setVoltage < MAX_VOLTAGE) {
          setVoltage ++;
          Serial.println(setVoltage, " Volts");
        }
        else if (setVoltage >= MAX_VOLTAGE) {
          Serial.println("Max voltage reached");
          state = PLASMA;
        }
        lastTime = millis();               // update time stamp
      }
      break;

    case PLASMA:
      if (!plasmaStarted) {
        plasmaTimer = millis();
        plasmaStarted = 1;
        Serial.println("Plasma Started");
      }
      if (millis() > plasmaTimer + PLASMA_TIME) {        // increase voltage every 100ms
        state = VOLTAGE_DOWN;
        plasmaStarted = 0;      // reset plasma timer
        Serial.println("Plasma Finished");
      }
      break;

    case VOLTAGE_DOWN:
      if (millis() - lastTime > VOLTAGE_STEP_TIME) {        // increase voltage every 100ms
        if (setVoltage > 0) {
          setVoltage --;                  // decrease voltage by 1 volt
          Serial.println(setVoltage, " Volts");
        }
        else if (setVoltage <= 0) {
          variacRelayState = 0; // turn on power to variac
          state = COOLDOWN;
        }
        lastTime = millis();               // update time stamp
      }
      break;

    case COOLDOWN:
      if (!cooldownStarted) {
        cooldownTimer = millis();
        cooldownStarted = 1;
        Serial.println("Cooldown Started");
      }
      if (millis() > cooldownTimer + COOLDOWN_TIME) {        // increase voltage every 100ms
        state = PUMPDOWN;
        cooldownStarted = 0;      // reset cooldown timer
        Serial.println("Cooldown Finished");
      }
      break;

    case ALARM:
      if (buttonType == 1) { // Square button pressed
        Serial.println("Alarm reset");
        alarmState = 0;      // Reset alarm state
        state = PUMP_DOWN;   // Start pumpdown again
        pumpStarted = 0;     // reset pump bool here just incase
      }
      else {
        printAlarmState();       // Print alarm reason every 1 second
        vacuumPump = 0;       // turn off pump routine
        variacRelayState = 0; // turn off power
        setVoltage = 0;       // set variac to 0v
      }
      break;
  }
}

void printAlarmState() {

  if (millis() - lastAlarmPrint > 1000) {
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
    lastAlarmPrint = millis();  // update timer
  }
}
