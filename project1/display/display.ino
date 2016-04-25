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
  display = new Display();
  input = new Input(display);
  led = new Led();
  parameters = new Parameters();
  parameters->setDefaultValues();
  monitor = new Monitor(led, parameters);
  thermometer = new Thermometer(display, monitor,parameters);
  accelerometer = new Accelerometer(parameters);
  bus = new Bus(thermometer,accelerometer, parameters);
}

void loop()
{
  bus->receiveBytes();
  thermometer->updateTemperature();
  thermometer->sendPeriodically();
  input->checkInput();
  display->update();
  delay(1000);
}
