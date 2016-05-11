#ifndef PARAMETERS_H
#define PARAMETERS_H

enum Parameter
{
  UPPER_TEMP_THRESHOLD,
  LOWER_TEMP_THRESHOLD,
  TEMP_PER_TIME_THRESHOLD,
  TOTAL_ACC_THRESHOLD,
  MAX_TEMP,
  MIN_TEMP,
  MAX_ACC_X,
  MAX_ACC_Y,
  MAX_ACC_Z,
  TEMP_UPDATE_INTERVAL,
  TEMP_UPDATE_DELTA,
  CALIBRATION_TEMP,
  CALIBRATION_MIN_X,
  CALIBRATION_MAX_X,
  CALIBRATION_MIN_Y,
  CALIBRATION_MAX_Y,
  CALIBRATION_MIN_Z,
  CALIBRATION_MAX_Z 
};

class Parameters { 
private: 
    double v[30];
public:
 void setMinMaxDefaultValues(){
      v[MAX_TEMP] = 20;
      v[MIN_TEMP] = 20;
      v[MAX_ACC_X] = 0;
      v[MAX_ACC_Y] = 0;
      v[MAX_ACC_Z] = 0;
  }
  
  void setDefaultValues(){
      v[UPPER_TEMP_THRESHOLD] = 30;
      v[LOWER_TEMP_THRESHOLD] = 10;
      v[TEMP_PER_TIME_THRESHOLD] = 5;
      v[TOTAL_ACC_THRESHOLD] = 3;
      v[TEMP_UPDATE_INTERVAL] = 60;
      v[TEMP_UPDATE_DELTA] = 3;
      v[CALIBRATION_TEMP] = 0;
      v[CALIBRATION_MIN_X] = -1.4;
      v[CALIBRATION_MAX_X] = 1.25;
      v[CALIBRATION_MIN_Y] = -1.44;
      v[CALIBRATION_MAX_Y] = 1.25;
      v[CALIBRATION_MIN_Z] = -1.66;
      v[CALIBRATION_MAX_Z] = 1.42;
      setMinMaxDefaultValues();
  }

  void setValue(Parameter p, double value){
    v[p]=value;
  }

  double getValue(Parameter p){
    return v[p];
  }
  
};

#endif
