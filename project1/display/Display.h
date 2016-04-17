#ifndef DISPLAY_H
#define DISPLAY_H
#include <SoftwareSerial.h>

#include "Arduino.h"

enum Line {
  CUR_TEMP,
  TEMP_MAX,
  TEMP_MIN,
  LINE_COUNT
};

class Display {
public:
  Display();
  ~Display();
  void update();
  void scroll(int lines);
  void resetValues();
  void setTemp(int degrees);
private:
  static const int LED_PIN = 2;
  static const int LCD_DELAY = 100;
  Line curTopLine;
  SoftwareSerial* lcd;
  int tempDeg;
  int minTempDeg;
  int maxTempDeg;

  
  void showCurrentTemp();
  void showMinTemp();
  void showMaxTemp();
  void clearDisplay();
  void lcdPosition(int row, int col);
  void showLine(Line line);
};



#endif
