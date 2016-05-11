#ifndef LED_H
#define LED_H

#include "Arduino.h"

class Led {
public:
  Led(int lid);
  void init();
  void setActive(bool isActive);
private:
  int ledId;
};

#endif

