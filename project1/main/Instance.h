#ifndef INSTANCE_H
#define INSTANCE_H

#include "Monitor.h"
#include "Accelerometer.h"
#include "Parameters.h"
#include "Thermometer.h"
#include "LED.h"
#include "Bus.h"
#include "Display.h"
#include "Input.h"

//the one place where all instances of objects can be accessed from :)

class Instance { 
public:
  static Accelerometer* accelerometer;
  static Monitor* monitor;
  static Parameters* parameters;
  static Thermometer* thermometer;
  static LED* led;
  static Bus* bus;
  static Display* display;
  static Input* input;
};

#endif
