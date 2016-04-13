#include "Instance.h"

void setup(){
  Instance::parameters->setDefaultValues();
  //TODO: Call the init methods of instances that require it here
}

void loop(){
 Instance::monitor->monitor();
 Instance::bus->receiveBytes();
 Instance::display->update();
 Instance::input->checkInput();
 Instance::thermometer->sendPeriodically();
}

