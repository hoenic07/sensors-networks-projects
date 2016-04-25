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
    if(activeAlarms[3] == false){
      activeAlarms[3] = true;
      led->on(Led::LED1);
      bus->sendMessage(ALARM_ACC);
    }
  }
  else{
    activeAlarms[3] = false;
    led->off(Led::LED1);
  }
}

void Monitor::updateTemperature() {
  int temp = thermometer->getTemperature();
  double tempDiff = thermometer->getTempDiff();
  
  double maxTemp = parameters->getValue(UPPER_TEMP_THRESHOLD);
  double minTemp = parameters->getValue(LOWER_TEMP_THRESHOLD);
  double dTThr = parameters->getValue(TEMP_PER_TIME_THRESHOLD);

  if(temp < minTemp){
    if(activeAlarms[0] == false){
      activeAlarms[0] = true;
      bus->sendMessage(ALARM_TEMP_MIN);
    }
  }else{
    activeAlarms[0] = false;
  }
  
  if(temp > maxTemp){
    if(activeAlarms[1] == false){
      activeAlarms[1] = true;
      bus->sendMessage(ALARM_TEMP_MAX);
    }
  }else{
    activeAlarms[1] = false;
  }
  
   if(tempDiff > dTThr){
    if(activeAlarms[2] == false){
      activeAlarms[2] = true;
      bus->sendMessage(ALARM_TEMP_DT);
    }
  }else{
    activeAlarms[2] = false;
  }

  if(activeAlarms[0] || activeAlarms[1] || activeAlarms[2]){
    led->on(Led::LED2);
  }else{
    led->off(Led::LED2);
  }

  //I know it's not the best place for this, but better than nothing :P
  bool shouldSendPeriodically = thermometer->shouldSendTemperature();
  if(shouldSendPeriodically){
    bus->sendMessage(RESP_TEMP,temp,VALUE);
  }
  
}

