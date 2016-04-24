#include "Monitor.h"
#include "Instance.h"
#include "Arduino.h"


//<<constructor>>
Monitor::Monitor(){
  Instance::led->init();
}

//<<destructor>>
Monitor::~Monitor(){}


void Monitor::monitor(){
  double x = Instance::accelerometer->getX();
  double y = Instance::accelerometer->getY();
  double z = Instance::accelerometer->getZ();
  double totalAcc = x*x+y*y+z*z;
  double thr = Instance::parameters->TOTAL_ACC_THRESHOLD;

  if(totalAcc > thr*thr){ //square thr to avoid sqrt
    //TODO: Fire alarm over bus
    Instance::led->on(LED::LED1);
  }
  else{
    Instance::led->off(LED::LED1);
  }

  double temp = Instance::thermometer->getTemperature();
  double maxTemp = Instance::parameters->UPPER_TEMP_THRESHOLD;
  double minTemp = Instance::parameters->LOWER_TEMP_THRESHOLD;
  double dTThr = Instance::parameters->TEMP_PER_TIME_THRESHOLD;
  if(temp > maxTemp || temp < minTemp){ //TODO: Check dT/dt threshold
    //TODO: Fire alarm over bus
    Instance::led->on(LED::LED2);
  }
  else{
    Instance::led->off(LED::LED2);
  }
  
}

