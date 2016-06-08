#include "RGBLed.h"

RGBLed::RGBLed(int lidRed, int lidGreen, int lidBlue) {
  ledIdRed = lidRed;
  ledIdGreen = lidGreen;
  ledIdBlue = lidBlue;
}

void RGBLed::init() {
    pinMode(ledIdRed, OUTPUT);
    pinMode(ledIdGreen, OUTPUT);
    pinMode(ledIdBlue, OUTPUT);
}

void RGBLed::setColor(int red, int green, int blue){
  analogWrite(ledIdRed, red);
  analogWrite(ledIdGreen, green);
  analogWrite(ledIdBlue, blue);
}

