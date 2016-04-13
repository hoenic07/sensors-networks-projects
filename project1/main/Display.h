#ifndef DISPLAY_H
#define DISPLAY_H

#include "Arduino.h"

class Display {
public:
  Display();
  ~Display();
  void update();
  void nextDisplay();
private:
  int currentDisplayedIndex;
  void display1();
  void display2();
  void display3();
  void clearDisplay();
};



#endif
