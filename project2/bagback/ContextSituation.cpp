#include "ContextSituation.h"


ContextSituation::ContextSituation(){
  piezo = new Piezo();
  piezo->init();

  standingLed = new Led(LED_ID_STANDING);
  standingLed->init();
  walkingLed = new Led(LED_ID_WALKING);
  walkingLed->init();
  runningLed = new Led(LED_ID_RUNNING);
  runningLed->init();
}

ContextSituation::~ContextSituation() {
}

void ContextSituation::update() {
  if(lumen > THRESHOLD_OPEN) {
    piezo->setActivated(true);
  }else{
    piezo->setActivated(false);
  }

  runningLed->setActive(false);
  walkingLed->setActive(false);
  standingLed->setActive(false);

  if(windowedAcceleration > 1){
  	runningLed->setActive(true);
  }
  else if(windowedAcceleration > 0.1){
  	walkingLed->setActive(true);
  }
  else{
    Serial.println("Standing");
  	standingLed->setActive(true);
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

