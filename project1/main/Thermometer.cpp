#include "Thermometer.h"
#include "Instance.h"

Thermometer::Thermometer(){
  
}

Thermometer::~Thermometer(){
  
}

void Thermometer::init(){
  //TODO: Define the table with the static values here
}

double Thermometer::getTemperature(){
  return 10; //TODO
}

void Thermometer::sendPeriodically(){
  double interval = Instance::parameters->TEMP_UPDATE_INTERVAL;
  double delta = Instance::parameters->TEMP_UPDATE_DELTA;
  //TODO: Send if condition is true
}

