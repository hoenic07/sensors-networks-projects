#include "Thermometer.h"
#include "Arduino.h"


Thermometer::Thermometer(Parameters* p){
  parameters = p;
  curTempDeg = -1;
}

Thermometer::~Thermometer(){
  
}

void Thermometer::init(){
}

void Thermometer::updateTemperature(){  
  int tempValue = analogRead(A2);
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
}

bool Thermometer::shouldSendTemperature(){
  double interval = parameters->getValue(TEMP_UPDATE_INTERVAL);
  double delta = parameters->getValue(TEMP_UPDATE_DELTA);

  int fq=3; // timer frequency
  
  time++;
  
  if(interval!=0&&time>=interval*fq){
    time=0;
    return true;
  }

  if(delta!=0&&abs(lastSendDeltaTemp-curTempDeg)>delta){
    lastSendDeltaTemp=curTempDeg;
    return false;
  }

  return false;
}

double Thermometer::getTemperature() {
  return curTempDeg + calibrationDiff;
}

double Thermometer::getTempDiff() {
  return tempDiff;
}

void Thermometer::setCalibrationTemp(double tempDeg) {
  calibrationDiff = tempDeg - curTempDeg;
}

void Thermometer::updateTimeDiff(){
  timeValues[pos] = millis();
  tempValues[pos] = curTempDeg;

  long timeDiff = 0;
  bool calculatedDiff = false;

  int previousPos = pos;
  int currentPos = previousPos - 1;

  while (currentPos >= 0) {
    timeDiff += timeValues[previousPos] - timeValues[currentPos];

    if (timeDiff >= timeTms) {
      tempDiff = tempValues[pos] - tempValues[currentPos];
      calculatedDiff = true;
      break;
    }
    previousPos--;
    currentPos = previousPos - 1;
  }

  if (!calculatedDiff) {
    if (timeValues[MAX_VALUES_TEMP_DIFF - 1] != 0) {

      previousPos = 0;
      currentPos = MAX_VALUES_TEMP_DIFF - 1;

      while (currentPos > pos) {
        timeDiff += timeValues[previousPos] - timeValues[currentPos];

        if (timeDiff >= timeTms) {
          tempDiff = tempValues[pos] - tempValues[currentPos];
          calculatedDiff = true;
          break;
        }
        previousPos = currentPos;
        currentPos--;
      }
    }
  }

  pos++;
  if (pos >= MAX_VALUES_TEMP_DIFF) {
    pos = 0;
  }
}
