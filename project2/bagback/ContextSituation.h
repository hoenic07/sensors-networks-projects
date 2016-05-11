#ifndef CONTEXTSITUATION_H
#define CONTEXTSITUATION_H

#include "Piezo.h"

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
  const int THRESHOLD_OPEN = 500;
  const int RINGBUFFER_SIZE=20*2;
  double totalAccRingBuffer[RINGBUFFER_SIZE];
  int ringBufferPos=0;
  double ringBufferSum=0;
  double windowedAcceleration=0;
};

#endif
