#include "Arduino.h"

#include "pins.hpp"
#include "settings.hpp"
#include "util.hpp"
#include "oled.hpp"
#include "timer.hpp"

class Buttons {
  public:
    enum Button {
      NONE,
      UP,
      DOWN,
      SELECT,
    };

    void setup() {
      pinMode(SAFETY_SWITCH, INPUT);
      pinMode(BUTTONS, INPUT);
      pinMode(FC, OUTPUT);
      digitalWrite(FC, HIGH); // FC needed for A0 to work???
    }

    Button pressed() {

      int buttonValue = analogRead(Pins::BUTTONS);
      // delay(100);
   //   if (Timer.pressed(20) == true) {
        if (buttonValue > 3300 && buttonValue < 3600) {
          debugln("Button SELECT pressed");
          Oled.displayln("Button SELECT pressed");
          return Button::SELECT;
        }
        else if (buttonValue > 2300 && buttonValue < 2500) {
          debugln("Button DOWN pressed");
          Oled.displayln("Button DOWN pressed");
          return Button::DOWN;
        }
        else if (buttonValue > 1500 && buttonValue < 1700) {
          debugln("Button UP pressed");
          Oled.displayln("Button UP pressed");
          return Button::UP;
        }
        return Button::NONE;
 //     }
    }
};

bool isCoverRemoved() {
  pinMode(SAFETY_SWITCH, INPUT);
  return digitalRead(SAFETY_SWITCH) == HIGH;
}
