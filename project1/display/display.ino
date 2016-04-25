// include the library code:
//#include "Instance.h"
#include "Display.h"
#include "Input.h"
#include "Thermometer.h"
#include "Monitor.h"
#include "Led.h"
#include "Bus.h"

Display* display;
Thermometer* thermometer;
Input* input;
Led* led;
Monitor* monitor;
Parameters* parameters;
Accelerometer* accelerometer;
Bus* bus;

void setup()
{
  parameters = new Parameters();
  parameters->setDefaultValues();
  led = new Led();
  accelerometer = new Accelerometer(parameters);
  display = new Display(parameters,accelerometer);
  input = new Input(display, parameters);
  monitor = new Monitor(led, parameters);
  thermometer = new Thermometer(display, monitor,parameters);
  bus = new Bus(thermometer,accelerometer, parameters);
}

void loop()
{
  bus->receiveBytes();
  thermometer->updateTemperature();
  thermometer->sendPeriodically();
  input->checkInput();
  display->update();
  delay(100);
}
