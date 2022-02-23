#pragma once

#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"

#include "util.hpp"

class _Oled {
  public:

    void begin() {
      oled.begin(&Adafruit128x64, 0x3C);
      oled.setFont(System5x7);
      oled.setScrollMode(SCROLL_MODE_AUTO);
      oled.clear();
    }

    void displayln () {
#ifdef OLED
      oled.println();
#endif
    }

    template <typename T, typename... Types>
    void displayln(T first, Types... other)
    {
#ifdef OLED
      oled.print(first);
      displayln(other...) ;
#endif
    }

  public:
    SSD1306AsciiWire oled;

};

extern _Oled Oled;
