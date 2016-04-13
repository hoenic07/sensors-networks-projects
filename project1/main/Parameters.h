#ifndef PARAMETERS_H
#define PARAMETERS_H

class Parameters { 
public:
  double UPPER_TEMP_THRESHOLD = 0;
  double LOWER_TEMP_THRESHOLD = 0;
  double TEMP_PER_TIME_THRESHOLD = 0;
  double TOTAL_ACC_THRESHOLD = 0;
  double MAX_TEMP = 0;
  double MIN_TEMP = 0;
  double MAX_ACC_X = 0;
  double MAX_ACC_Y = 0;
  double MAX_ACC_Z = 0;
  double TEMP_UPDATE_INTERVAL = 0;
  double TEMP_UPDATE_DELTA = 0;
  double CALIBRATION_TEMP = 0;
  double CALIBRATION_MIN_X = 0;
  double CALIBRATION_MAX_X = 0;
  double CALIBRATION_MIN_Y = 0;
  double CALIBRATION_MAX_Y = 0;
  double CALIBRATION_MIN_Z = 0;
  double CALIBRATION_MAX_Z = 0;
  void setDefaultValues(){
      //TODO: Set correct default values here;
  }
};

#endif
