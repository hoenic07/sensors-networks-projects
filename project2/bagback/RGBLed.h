#ifndef RGBLED_H
#define RGBLED_H

#include "Arduino.h"

class RGBLed {
public:
  RGBLed(int lidRed, int lidGreen, int lidBlue);
  void init();
  void setColor(int red, int green, int blue);
private:
  int ledIdRed;
  int ledIdGreen;
  int ledIdBlue;
};

#endif
