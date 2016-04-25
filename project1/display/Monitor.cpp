#include "Monitor.h"
#include "Arduino.h"


Monitor::Monitor(Led* l, Parameters* p, Bus* b, Thermometer* t, Accelerometer* a){
  led = l;
  parameters = p;
  bus = b;
  thermometer = t;
  accelerometer=a;
}

Monitor::~Monitor(){}

void Monitor::update() {
  updateAccelerometer();
  updateTemperature();
}

void Monitor::updateAccelerometer() {
  double x = accelerometer->getX();
  double y = accelerometer->getY();
  double z = accelerometer->getZ();
  double totalAcc = x * x + y * y + z * z;
  double thr = parameters->getValue(TOTAL_ACC_THRESHOLD);

  if(totalAcc > thr*thr){ //square thr to avoid sqrt
    led->on(Led::LED1);
    bus->sendMessage(ALARM_ACC);
  }
  else{
    led->off(Led::LED1);
  }
}

void Monitor::updateTemperature() {
  int temp = thermometer->getTemperature();
  double maxTemp = parameters->getValue(UPPER_TEMP_THRESHOLD);
  double minTemp = parameters->getValue(LOWER_TEMP_THRESHOLD);
  double dTThr = parameters->getValue(TEMP_PER_TIME_THRESHOLD);
  if(temp > maxTemp || temp < minTemp){ //TODO: Check dT/dt threshold
    led->on(Led::LED2);
    bus->sendMessage(ALARM_TEMP);
  }
  else{
    led->off(Led::LED2);
  }
}

