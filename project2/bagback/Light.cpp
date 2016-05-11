#include "Light.h"
#include "Arduino.h"

Light::Light(){
}

Light::~Light(){
}

void Light::init() {
}

double Light::getLumen() {
  return lumen;
}

void Light::update() {
  int val = analogRead(A0);

  lumen = map(val, 10, 1023, 1000, 0);

}
