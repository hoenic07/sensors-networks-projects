#ifndef MONITOR_H
#define MONITOR_H

#include "Led.h"
#include "Parameters.h"
#include "Bus.h"
#include "Thermometer.h"

class Monitor {
public:
  Monitor(Led* l, Parameters* p, Bus* b, Thermometer* t, Accelerometer* a);
  ~Monitor();
  void update();
private:
  void updateTemperature();
  void updateAccelerometer();
  Led* led;
  Bus* bus;
  Thermometer* thermometer;
  Parameters* parameters;
  bool activeAlarms[4]={}; //0...TEMP_MIN, 1...TEMP_MAX, 2...TEMP_DT, 3...ACC
  Accelerometer *accelerometer;
};



#endif
