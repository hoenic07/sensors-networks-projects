#include "Monitor.h"
#include "Arduino.h"


Monitor::Monitor(Led* l, Parameters* p){
  led = l;
  parameters = p;
}

Monitor::~Monitor(){}

void Monitor::updateAccelerometer(double x, double y, double z) {
  double totalAcc = x * x + y * y + z * z;
  double thr = parameters->getValue(TOTAL_ACC_THRESHOLD);

  if(totalAcc > thr*thr){ //square thr to avoid sqrt
    //TODO: Fire alarm over bus
   // led->on(Led::LED1);
  }
  else{
    led->off(Led::LED1);
  }
}

void Monitor::updateTemperature(int temp) {
  double maxTemp = parameters->getValue(UPPER_TEMP_THRESHOLD);
  double minTemp = parameters->getValue(LOWER_TEMP_THRESHOLD);
  double dTThr = parameters->getValue(TEMP_PER_TIME_THRESHOLD);
  if(temp > maxTemp || temp < minTemp){ //TODO: Check dT/dt threshold
    //TODO: Fire alarm over bus
    led->on(Led::LED2);
  }
  else{
    led->off(Led::LED2);
  }
}

