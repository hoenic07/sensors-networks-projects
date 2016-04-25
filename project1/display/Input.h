#ifndef INPUT_H
#define INPUT_H

#include "Arduino.h"
#include "Display.h"
#include "Parameters.h"

class Input {
public:
  Input(Display* d, Parameters* p);
  ~Input();
  void checkInput();
private:
  int btnPin;
  int pressCount=0;
  int lastRotarySection=0;
  const double ROTARY_SECTION_SIZE = 1024.0 / 6;
  bool isClosed=false;
  const int MIN_VALID_PRESS_COUNT=2;
  Display* display;
  Parameters* parameters;
  void rotaryEncoderChanged();
};



#endif
