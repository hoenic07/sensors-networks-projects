#include "Light.h"
#include "ContextSituation.h"
#include "Accelerometer.h"

// Objects 
Parameters* parameters;
Accelerometer* accelerometer;
Light* light;
ContextSituation* contextSituation;

// Variables
int samplePeriod = 0;
int cntProcess = 0;

// Constants
const int SAMPLE_FREQUENCY=20;
const int PROCESS_FREQUENCY=2;

void sampleTask();
void processTask();

void setup() {
  Serial.begin(9600);

  parameters = new Parameters();
  parameters->setDefaultValues();

  accelerometer = new Accelerometer(parameters);
  light = new Light();
  contextSituation = new ContextSituation();

  samplePeriod = 1000 / SAMPLE_FREQUENCY;
}

void loop() {
  long millisBegin = millis();

  // Sample task
  sampleTask();

  // Process task
  if(cntProcess == SAMPLE_FREQUENCY / PROCESS_FREQUENCY){
    cntProcess=0;
    processTask();
  }else{
    cntProcess++;
  }

  //control the period. remove the execution time
  long sleepTime = samplePeriod - millis() - millisBegin;

  // Check if deadline was met
  if(sleepTime < 0){
    Serial.println("Deadline not met!");
    sleepTime=0;
  }
  
  delay(sleepTime);
}

void sampleTask(){
  accelerometer->update();
  light->update();

  double x = accelerometer->getX();
  double y = accelerometer->getY();
  double z = accelerometer->getZ();
  double totalAcc = accelerometer->getTotalAcceleration();

  contextSituation->setAcc(x, y,z);

  double lumen= light->getLumen();
  contextSituation->setLumen(lumen);
}

void processTask(){
  contextSituation->update();
}

