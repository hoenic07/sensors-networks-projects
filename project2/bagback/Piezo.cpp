#include "Piezo.h"
#include "Arduino.h"

Piezo::Piezo() { 
}

Piezo::~Piezo() { 
  
}

void Piezo::init() {
  pinMode(13, OUTPUT);
}

void Piezo::setActivated(bool isActive) {
  
  digitalWrite(13, LOW);
  if(isActive) {
    digitalWrite(13, 10);
  }else{
    digitalWrite(13, 0);
  }
}
