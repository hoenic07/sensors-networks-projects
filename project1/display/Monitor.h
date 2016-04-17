#ifndef MONITOR_H
#define MONITOR_H

#include "Led.h"
#include "Parameters.h"

class Monitor {
public:
  Monitor(Led* l, Parameters* p);
  ~Monitor();
  void updateTemperature(int temp);
  void updateAccelerometer(double x, double y, double z);
private:
  Led* led;
  Parameters* parameters;
};



#endif
