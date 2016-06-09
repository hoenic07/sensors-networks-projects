#ifndef CONTEXTSITUATION_H
#define CONTEXTSITUATION_H

#include "Piezo.h"
#include "Led.h"
#include "RGBLed.h"
#include "AccelerometerAnalyzer.h"

class ContextSituation { 
public:
  ContextSituation();
  ~ContextSituation();
  void update();
  void setAcc(double x, double y, double z);
  void setTemperature(double t);
  void setLumen(double l);
private:
  double temp;
  double lumen;
  Piezo* piezo;
  Led* standingLed;
  Led* walkingLed;
  Led* runningLed;
  RGBLed* rgbLed;

  int discoCnt = 0;
  const int DISCO_CNT_MAX = 3;
  
  const int THRESHOLD_OPEN = 500;
  AccelerometerAnalyzer* accAnalyzer;
  const int LED_ID_STANDING = 7;
  const int LED_ID_WALKING = 6;
  const int LED_ID_RUNNING = 5;
  const int LED_ID_RED = 10;
  const int LED_ID_GREEN = 8;
  const int LED_ID_BLUE = 9;

  void applyDiscoMode(boolean active);
};

#endif
