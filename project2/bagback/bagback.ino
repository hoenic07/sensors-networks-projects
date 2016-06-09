#include "Thermometer.h"
#include "Bus.h"
#include "Light.h"
#include "ContextSituation.h"

// Objects 
Parameters* parameters;
Thermometer* thermometer;
Accelerometer* accelerometer;
Light* light;
Bus* bus;
ContextSituation* contextSituation;

// Variables
int samplePeriod = 0;
int cntProcess = 0;

// Constants
const int SAMPLE_FREQUENCY=20;
const int PROCESS_FREQUENCY=5;

void sampleTask();
void processTask();

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  parameters = new Parameters();
  parameters->setDefaultValues();

  accelerometer = new Accelerometer(parameters);
  thermometer = new Thermometer(parameters);
  light = new Light();
  contextSituation = new ContextSituation();

  samplePeriod = 1000/SAMPLE_FREQUENCY;
}

void loop() {
  long millisBegin = millis();

  // Sample task
  sampleTask();

  // Process task
  if(cntProcess == SAMPLE_FREQUENCY/PROCESS_FREQUENCY){
    cntProcess=0;
    processTask();
  }
  else cntProcess++;

  if(false){
    Serial.println(millisBegin);
    /*Serial.print(";");
    Serial.print(x);
    Serial.print(";");
    Serial.print(y);
    Serial.print(";");
    Serial.print(z);
    Serial.print(";");
    Serial.print(totalAcc);
    Serial.print(";");
    Serial.print(temp);
    Serial.print(";");
    Serial.println(lumen);*/
  }

  //control the period. remove the execution time
  long sleepTime = samplePeriod - (millis()-millisBegin);
  //Serial.println(sleepTime);

  // Check if deadline was met
  if(sleepTime<0){
    Serial.println("Deadline not met!");
    sleepTime=0;
  }
  
  delay(sleepTime);
}

void sampleTask(){
  accelerometer->update();
  thermometer->updateTemperature();
  light->update();

  double x = accelerometer->getX();
  double y = accelerometer->getY();
  double z = accelerometer->getZ();
  double totalAcc = accelerometer->getTotalAcceleration();

  contextSituation->setAcc(x, y,z);

  double temp = thermometer->getTemperature();
  contextSituation->setTemperature(temp);
  double lumen= light->getLumen();
  contextSituation->setLumen(lumen);
}

void processTask(){
  contextSituation->update();
}

