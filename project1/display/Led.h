#ifndef LED_H
#define LED_H

#include "Arduino.h"

class Led {
public:
  static const int LED1 = 13; 
  static const int LED2 = 12;
  void init(){
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
  }

  void on(int ledId){
    digitalWrite(ledId, HIGH);
  }

  void off(int ledId){
    digitalWrite(ledId, LOW);
  }
};

#endif
