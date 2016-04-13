#include "Accelerometer.h"
#include "Arduino.h"

const int ACC_X_PIN = 2;
const int ACC_Y_PIN = 3;
const int ACC_Z_PIN = 4;

//<<constructor>>
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



