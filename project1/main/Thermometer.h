#ifndef THERMOMETER_H
#define THERMOMETER_H

class Thermometer {
public:
  Thermometer();
  ~Thermometer();
  void init();
  double getTemperature();
  void sendPeriodically();
};



#endif
