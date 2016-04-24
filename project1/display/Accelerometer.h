#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

class Accelerometer { 
public:
  Accelerometer();
  ~Accelerometer();
    void init();
  double getX();
  double getY();
  double getZ();
private:
  double voltToG(int volt);
  
  const int ACC_X_PIN = 2;
  const int ACC_Y_PIN = 3;
  const int ACC_Z_PIN = 4;
};

#endif
