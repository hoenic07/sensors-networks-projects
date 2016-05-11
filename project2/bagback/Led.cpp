#include "Led.h"

Led::Led(int lid) {
  ledId = lid;
}

void Led::init() {
    pinMode(ledId, OUTPUT);
}

void Led::setActive(bool isActive) {
  if(isActive) {
    digitalWrite(ledId, HIGH);
  }else{
    digitalWrite(ledId, LOW);
  }
}
