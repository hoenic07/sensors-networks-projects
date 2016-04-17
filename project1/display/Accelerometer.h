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
};

#endif
