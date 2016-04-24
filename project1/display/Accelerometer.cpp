#include "Accelerometer.h"
#include "Arduino.h"


Accelerometer::Accelerometer(){
}

//<<destructor>>
Accelerometer::~Accelerometer(){}


void Accelerometer::init(){
}

//get acceleration on X-axis
double Accelerometer::getX(){
  int val = analogRead(ACC_X_PIN);
  return voltToG(val);
}

//get acceleration on Y-axis
double Accelerometer::getY(){
  int val = digitalRead(ACC_X_PIN);
  return voltToG(val);
}

//get acceleration on Z-axis
double Accelerometer::getZ(){
  int val = digitalRead(ACC_X_PIN);
  return voltToG(val);
}

double Accelerometer::voltToG(int volt){
  return 0;
}



