#ifndef LED_H
#define LED_H

#include "Arduino.h"

class LED {
public:
  static const int LED1 = 10; //TODO: Set correct pin here and below
  static const int LED2 = 11;
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
