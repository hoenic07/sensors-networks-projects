#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

#include "Parameters.h"

class Accelerometer { 
public:
  Accelerometer(Parameters* p);
  ~Accelerometer();
  void init();
  double getX();
  double getY();
  double getZ();
  double getPitch();
  double getRoll();
  double getTheta();
  double getTotalAcceleration();
  void update();
private:
  double voltToG(int volt, int axis);
  double getParameterForAxis(int minMax, int axis);
  Parameters* parameters;
  double x;
  double y;
  double z;
  double pitch;
  double roll;
  double theta;
};

#endif
