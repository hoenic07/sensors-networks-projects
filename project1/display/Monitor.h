#ifndef MONITOR_H
#define MONITOR_H

#include "Led.h"
#include "Parameters.h"
#include "Bus.h"
#include "Thermometer.h"

class Monitor {
public:
  Monitor(Led* l, Parameters* p, Bus* b, Thermometer* t);
  ~Monitor();
  void updateTemperature();
  void updateAccelerometer(double x, double y, double z);
private:
  Led* led;
  Bus* bus;
  Thermometer* thermometer;
  Parameters* parameters;
};



#endif
