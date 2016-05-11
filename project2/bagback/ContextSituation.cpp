#include "ContextSituation.h"


ContextSituation::ContextSituation(){
  piezo = new Piezo();
  piezo->init();
}

ContextSituation::~ContextSituation() {
}

void ContextSituation::update() {
  if(lumen > THRESHOLD_OPEN) {
    piezo->setActivated(true);
  }else{
    piezo->setActivated(false);
  }

  if(windowedAcceleration > 1){
    Serial.println("Running");
  }
  else if(windowedAcceleration > 0.1){
    Serial.println("Walking");
  }
  else{
    Serial.println("Standing");
  }
  
}

void ContextSituation::setAcc(double x, double y, double z){
  accX = x;
  accY = y;
  accZ = z;

  totalAcc = (x*x+y*y+z*z - 1); // calc total acceleration
  ringBufferSum+=totalAcc; // add the new acceleration to the sum
  ringBufferSum-=totalAccRingBuffer[totalAccRingBuffer]; // remove the old acceleration from the sum
  totalAccRingBuffer[totalAccRingBuffer]=totalAcc; // add to correct position
  ringBufferPos = (ringBufferPos+1)%RINGBUFFER_SIZE;  // set the index position of the next element
  windowedAcceleration=ringBufferSum / RINGBUFFER_SIZE; // calculate the average acceleration
}
void ContextSituation::setTemperature(double t){
  temp = t;
}
void ContextSituation::setLumen(double l){
  lumen = l;
}

