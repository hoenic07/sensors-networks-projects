#ifndef CONTEXTSITUATION_H
#define CONTEXTSITUATION_H

#include "Piezo.h"
#include "Led.h"

class ContextSituation { 
public:
  ContextSituation();
  ~ContextSituation();
  void update();
  void setAcc(double x, double y, double z);
  void setTemperature(double t);
  void setLumen(double l);
private:
  double accX;
  double accY;
  double accZ;
  double temp;
  double lumen;
  Piezo* piezo;
  Led* standingLed;
  Led* walkingLed;
  Led* runningLed;
  const int THRESHOLD_OPEN = 500;
  const int LED_ID_STANDING = 12;
  const int LED_ID_WALKING = 11;
  const int LED_ID_RUNNING = 10;
  const int RINGBUFFER_SIZE=20*2;
  double totalAccRingBuffer[RINGBUFFER_SIZE];
  int ringBufferPos=0;
  double ringBufferSum=0;
  double windowedAcceleration=0;
};

#endif
