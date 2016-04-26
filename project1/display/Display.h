#ifndef DISPLAY_H
#define DISPLAY_H
#include <SoftwareSerial.h>

#include "Arduino.h"
#include "Thermometer.h"
#include "Accelerometer.h"
#include "Parameters.h"

enum Line {
  CUR_TEMP,
  TEMP_MAX,
  TEMP_MIN,
  ACC_X,
  ACC_Y,
  ACC_Z,
  PITCH_ROLL,
};

class Display {
  public:
    Display(Parameters* p, Accelerometer* a, Thermometer* t);
    ~Display();
    void update();
    void scroll(int newLine);
  private:
    static const int LED_PIN = 2;
    static const int LCD_DELAY = 100;
    Parameters* parameters;
    Accelerometer* accelerometer;
    Thermometer* thermometer;
    Line curTopLine;
    SoftwareSerial* lcd;
    void showCurrentTemp();
    void showMinTemp();
    void showMaxTemp();
    void clearDisplay();
    void lcdPosition(int row, int col);
    void showLine(Line line);
    void printFloat(double val);
    void showAccX();
    void showAccY();
    void showAccZ();
    void showPitchRoll();
};



#endif
