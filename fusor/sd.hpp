#pragma once

#include "FS.h"
#include "SD.h"
#include "SPI.h"
#include "pins.hpp"

  pinMode(FC , OUTPUT);  
  digitalWrite(FC , HIGH);   

void setup(){
   if(SD.begin()){
  Serial.println("Card Mount: success");
  display.println("Card Mount: success");
  display.setCursor(0, 20);
  Serial.print("Card Type: ");
  display.print("Card Type: ");

  display.setCursor(65,20 );
    if(cardType == CARD_MMC){
        Serial.println("MMC");
        display.println("MMC");
    } else if(cardType == CARD_SD){
        Serial.println("SDSC");
        display.println("SDSC");
    } else if(cardType == CARD_SDHC){
        Serial.println("SDHC");
        display.println("SDHC");
    } else {
        Serial.println("Unknown");
        display.println("Unknown");
    }

  display.setCursor(0, 35);
  int cardSize = SD.cardSize() / (1024 * 1024);
  Serial.printf("Card Size: %lluMB\n", cardSize);
  display.println("Card Size:");
  display.setCursor(65,35);
  display.println(cardSize);
}

  if(!SD.begin()){
  display.setCursor(35, 15);
  Serial.println("NO SD card");  
  display.println("NO SD card");           
}
Serial.println("SD setup complete");
}
