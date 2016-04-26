#ifndef THERMOMETER_H
#define THERMOMETER_H

#include "Accelerometer.h"

class Thermometer {
private:
  static const int MAX_VALUES_TEMP_DIFF = 15;
  static const int timeTms = 10 * 1000; //10 seconds = 10 000ms
  
  Parameters* parameters;
  double refValues[44] = {1.0, 445.673936, 50, 149.2655013, 100, 117.9296624, 150, 100.5952676, 200, 88.44942453, 250, 78.9525832, 300, 71.02607689, 350, 64.10960824, 400, 57.87105707, 450, 52.09247706, 500, 46.61727072, 550, 41.32210074, 600,36.09952575, 650, 30.84479968, 700, 25.44259556, 750, 19.7489962, 800, 13.56014645, 850, 6.545460153, 900, -1.92807308, 950, -13.42396818, 1000, -34.84616813, 1023, -81.19677621};
  double curTempDeg;
  double tempDiff;
  int time=0;
  double lastSendDeltaTemp=0;
  double calibrationDiff = 0;

  int pos = 0;
  double tempValues[MAX_VALUES_TEMP_DIFF]{};
  unsigned long timeValues[MAX_VALUES_TEMP_DIFF]={};

  void updateTimeDiff();
public:
  Thermometer(Parameters* p);
  ~Thermometer();
  void init();
  void updateTemperature();
  bool shouldSendTemperature();
  double getTemperature();
  double getTempDiff();
  void setCalibrationTemp(double tempDeg);
};



#endif
