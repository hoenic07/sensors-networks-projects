#ifndef INPUT_H
#define INPUT_H

#include "Arduino.h"

class Input {
public:
  Input();
  ~Input();
  void checkInput();
private:
  void buttonPressed();
  void rotaryEncoderChanged();
};



#endif
