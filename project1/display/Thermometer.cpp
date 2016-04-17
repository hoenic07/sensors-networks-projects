#include "Thermometer.h"
#include "Arduino.h"


Thermometer::Thermometer(Display* d, Monitor* m){
  display = d;
  monitor = m;
}

Thermometer::~Thermometer(){
  
}

void Thermometer::init(){
}

void Thermometer::updateTemperature(){
  int tempValue = analogRead(A0);
  int targetIndex = 0;
  for(int i=2; i < sizeof(refValues) / sizeof(refValues[0]); i+=2) {
    double curTempV = refValues[i];
    
    if(tempValue < curTempV) {
      targetIndex = i;
      break;
    }
  }
  double temp;
  if(targetIndex == 0) {
    temp = refValues[1];
  }else{
    double v1 = refValues[targetIndex];
    double v2 = refValues[targetIndex - 2];
    
    double tempDeg1 = refValues[targetIndex + 1];
    double tempDeg2 = refValues[targetIndex -1];
  
    temp = tempDeg1 - (tempDeg1 - tempDeg2)/(v2 - v1) * (tempValue - v1);
  }
  display->setTemp(temp);
  monitor->updateTemperature(temp);

 
  
  
  //return temp;
}

void Thermometer::sendPeriodically(){
  //double interval = Instance::parameters->TEMP_UPDATE_INTERVAL;
  //double delta = Instance::parameters->TEMP_UPDATE_DELTA;
  //TODO: Send if condition is true
}

