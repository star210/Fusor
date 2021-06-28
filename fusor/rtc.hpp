#pragma once

#include "RTClib.h"  
#include "pins.hpp"

RTC_DS3231 rtc; 

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void setup(){
  
 if (! rtc.begin()) {
    Serial.println("No RTC found!");
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(15,15);
    display.println("No RTC found!");
    display.display();
    delay(2000);
    display.clearDisplay();
    display.display();
 }
 else{
 if (rtc.lostPower()) {
  
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(25, 15);
    display.println("RTC lost power");
    display.setCursor(30, 35);
    display.println("Set the time!");
    Serial.println("RTC lost power, setting the time!");
    display.display();
    delay(3000);
    display.clearDisplay();
    display.display();
 
    // If the RTC have lost power it will sets the RTC to the date & time this sketch was compiled in the following line
    // set time from computer time
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2021, 3, 30, 11, 55, 0));
  }

  rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); 
  int a=1;
  while(a<6)
 {
  displayTime();   // printing time function for oled
  a=a+1;
}
 }
 Serial.println("RTC setup complete");
}

 void displayTime(void) {
  DateTime now = rtc.now();
  display.setTextSize(1);             
  display.setTextColor(SSD1306_WHITE);       
 
  display.setCursor(10, 15);        
  display.print(now.year(), DEC);
  display.print('/');
  display.print(now.month(), DEC);
  display.print('/');
  display.print(now.day(), DEC);
  display.print(" ");
  display.print(daysOfTheWeek[now.dayOfTheWeek()]);

  display.setTextSize(2);
  display.setCursor(15, 30);  
  display.print(now.hour(), DEC);
  display.print(':');
  display.print(now.minute(), DEC);
  display.print(':');
  display.print(now.second(), DEC);
  display.println();
  delay(1000);
  display.display();
  display.clearDisplay();
