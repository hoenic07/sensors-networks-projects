#include "Accelerometer.h"
#include "Arduino.h"

const int ACC_X_PIN = 5;
const int ACC_Y_PIN = 4;
const int ACC_Z_PIN = 3;

//<<constructor>>
Accelerometer::Accelerometer(Parameters* p){
  parameters=p;
}

//<<destructor>>
Accelerometer::~Accelerometer(){}


void Accelerometer::init(){
}

void Accelerometer::update(){
   int val = analogRead(ACC_X_PIN);
  double maxAcc = parameters->getValue(MAX_ACC_X);
  x = voltToG(val,0);
  if(x>maxAcc){
    parameters->setValue(MAX_ACC_X, x);
  }
  

  val = analogRead(ACC_Y_PIN);
  maxAcc = parameters->getValue(MAX_ACC_Y);
  y = voltToG(val,1);
  if(y>maxAcc){
    parameters->setValue(MAX_ACC_Y, y);
  }

  val = analogRead(ACC_Z_PIN);
  maxAcc = parameters->getValue(MAX_ACC_Z);
  z = voltToG(val,2);
  if(z>maxAcc){
    parameters->setValue(MAX_ACC_Z, z);
  }

  pitch=atan(x/sqrt(y*y+z*z))*57.3; // 57.3 ~ 180/PI
  roll=atan(y/sqrt(x*x+z*z))*57.3;
  theta=atan(sqrt(y*y+x*x)/z)*57.3;
}

//get acceleration on X-axis
double Accelerometer::getX(){
  return x;
}

//get acceleration on Y-axis
double Accelerometer::getY(){
  return y;
}

//get acceleration on Z-axis
double Accelerometer::getZ(){
  return z;
}

double Accelerometer::getPitch(){
  return pitch; 
}

double Accelerometer::getRoll(){
  return roll;
}

double Accelerometer::getTheta(){
  return theta;
}

double Accelerometer::getTotalAcceleration() {
  return x*x + y*y + z*z;
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





