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
private:
  static const int LED_PIN = 2;
  static const int LCD_DELAY = 100;
  Line curTopLine;
  SoftwareSerial* lcd;
  double tempDeg;
  double minTempDeg;
  double maxTempDeg;

  
  void showCurrentTemp();
  void showMinTemp();
  void showMaxTemp();
  void display1();
  void display2();
  void display3();
  void clearDisplay();
  void lcdPosition(int row, int col);
  void showLine(Line line);
};



#endif
