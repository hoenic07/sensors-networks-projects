#include "Thermometer.h"
#include "Bus.h"
#include "Light.h"
#include "ContextSituation.h"

Parameters* parameters;
Thermometer* thermometer;
Accelerometer* accelerometer;
Light* light;
Bus* bus;
ContextSituation* contextSituation;

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  parameters = new Parameters();
  parameters->setDefaultValues();

  accelerometer = new Accelerometer(parameters);
  thermometer = new Thermometer(parameters);
  light = new Light();
  contextSituation = new ContextSituation();
}

void loop() {
  // put your main code here, to run repeatedly:

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

  contextSituation->update();
  

  Serial.print(millis());
  Serial.print(";");
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
  Serial.println(lumen);

  delay(50);
}
