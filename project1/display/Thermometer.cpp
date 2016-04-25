#include "Thermometer.h"
#include "Arduino.h"


Thermometer::Thermometer(Display* d, Parameters* p){
  display = d;
  parameters = p;
  curTempDeg = -1;
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
  curTempDeg = temp;

  double maxT = parameters->getValue(MAX_TEMP);
  double minT = parameters->getValue(MIN_TEMP);

  if(temp>maxT){
    parameters->setValue(MAX_TEMP,temp);
  }
  if(temp<minT){
    parameters->setValue(MIN_TEMP,temp);
  }

  display->setTemp(temp + calibrationDiff);
}

void Thermometer::sendPeriodically(){
  double interval = parameters->getValue(TEMP_UPDATE_INTERVAL);
  double delta = parameters->getValue(TEMP_UPDATE_DELTA);

  int fq=10; // timer frequency
  
  time++;
  
  if(time>=interval*fq){
    time=0;
    //TODO: Send temp here
  }

  if(abs(lastSendDeltaTemp-curTempDeg)>delta){
    lastSendDeltaTemp=curTempDeg;
    //TODO: Send temp here
  }
}

double Thermometer::getTemperature() {
  return curTempDeg + calibrationDiff;
}

void Thermometer::setCalibrationTemp(double tempDeg) {
  calibrationDiff = tempDeg - curTempDeg;
}

