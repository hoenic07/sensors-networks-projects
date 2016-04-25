#include "Accelerometer.h"
#include "Arduino.h"

const int ACC_X_PIN = 2;
const int ACC_Y_PIN = 3;
const int ACC_Z_PIN = 4;

//<<constructor>>
Accelerometer::Accelerometer(Parameters* p){
  parameters=p;
}

//<<destructor>>
Accelerometer::~Accelerometer(){}


void Accelerometer::init(){
}

//get acceleration on X-axis
double Accelerometer::getX(){
  int val = analogRead(ACC_X_PIN);
  return voltToG(val,0);
}

//get acceleration on Y-axis
double Accelerometer::getY(){
  int val = analogRead(ACC_Y_PIN);
  return voltToG(val,1);
}

//get acceleration on Z-axis
double Accelerometer::getZ(){
  int val = analogRead(ACC_Z_PIN);
  return voltToG(val,2);
}

double Accelerometer::getPitch(){
  double x = getX();
  double y = getY();
  double z = getZ();
  return atan(x/sqrt(y*y+z*z))*57.3; // 57.3 ~ 180/PI
}

double Accelerometer::getRoll(){
  double x = getX();
  double y = getY();
  double z = getZ();
  return atan(y/sqrt(x*x+z*z))*57.3;
}

double Accelerometer::getTheta(){
  double x = getX();
  double y = getY();
  double z = getZ();
  return atan(sqrt(y*y+x*x)/z)*57.3;
}

double Accelerometer::voltToG(int volt, int axis){
  double minVal = getParameterForAxis(0,axis);
  double maxVal = getParameterForAxis(1,axis);
  double g = map(volt, 662, 355, minVal*1000, maxVal*1000);
  return g / 1000;
}

double Accelerometer::getParameterForAxis(int minMax, int axis){
  if(minMax==0){
    switch(axis){
      case 0: return parameters->getValue(CALIBRATION_MIN_X);
      case 1: return parameters->getValue(CALIBRATION_MIN_Y);
      case 2: return parameters->getValue(CALIBRATION_MIN_Z);
      default: return 0;
    }
  }
  else if(minMax==1){
    switch(axis){
      case 0: return parameters->getValue(CALIBRATION_MAX_X);
      case 1: return parameters->getValue(CALIBRATION_MAX_Y);
      case 2: return parameters->getValue(CALIBRATION_MAX_Z);
      default: return 0;
    }
  }
  else return 0;
}





