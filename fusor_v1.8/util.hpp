#pragma once

#include <Arduino.h>

template<typename T>
void debug(T arg) {
#ifdef DEBUG
  Serial.print(arg);
  Serial.print(' ');
#endif
}

template<typename T, typename... Args>
void debug(T head, Args... tail) {
  debug(head);
  debug(tail...);
}

template<typename T, typename... Args>
void debugln(T head, Args... tail) {
#ifdef DEBUG
  debug(head, tail...);
  Serial.println();
#endif
}

template <typename T>
T vmap(T v, float imin, float imax, float omin, float omax) {
  return omin + (omax - omin) * ((v - imin) / (imax - imin));
}
