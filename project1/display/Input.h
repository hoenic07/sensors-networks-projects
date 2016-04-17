#ifndef INPUT_H
#define INPUT_H

#include "Arduino.h"
#include "Display.h"

class Input {
public:
  Input(Display* d);
  ~Input();
  void checkInput();
private:
  int btnPin;
  Display* display;
  void rotaryEncoderChanged();
};



#endif
