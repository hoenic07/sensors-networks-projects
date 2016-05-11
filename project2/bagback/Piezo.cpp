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
  if(isActive) {
    tone(13, 262, 10);
  }
}
