#ifndef BUS_H
#define BUS_H

#include <StackArray.h>
#include "Arduino.h"
#include "Thermometer.h"
#include "Accelerometer.h"

struct BusMessage{
  byte length;
  byte command;
  byte dataFormat;
  byte receiver;
  short data[2];
};


enum Receiver : byte {
  BUS,
  SENSOR
};

enum Command : byte {
  REQ_ACK,
  REQ_TEMP,
  RESP_TEMP,
  REQ_X,
  REQ_Y,
  REQ_Z,
  REQ_PITCH,
  REQ_ROLL,
  REQ_THETA,
  RESP_X,
  RESP_Y,
  RESP_Z,
  RESP_PITCH,
  RESP_ROLL,
  RESP_THETA,
  REQ_PARA,
  RESP_PARA,
  SET_PARA,
  ALARM_TEMP,
  ALARM_X,
  ALARM_Y,
  ALARM_Z,
  RESET_MINMAX,
  ACK,
  NACK,
  INVALID
};

enum DataFormat : byte {
  NO_DATA,
  VALUE,
  PARAMETER, 
  PARAMETER_AND_VALUE, 
};

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

class Bus {
public:
  Bus(Thermometer* t, Accelerometer* a);
  ~Bus();
  void sendMessage();
  void receiveBytes();
  void handleReceivedMessage(BusMessage msg);
  const int MESSAGE_START_BYTE = 0x55;
  const int MESSAGE_END_BYTE = 0xAA;
private:
  BusMessage messageFromBytes(byte bytes[]);
  int readByte();
  void sendBusMessage(BusMessage* msg);
  byte* receivedMessage;
  StackArray<int> receivedMessages;
  Thermometer* thermometer;
  Accelerometer* accelerometer;
  
  void processReceivedMessage(BusMessage* msg);
  void sendMessage(Command cmd);
  void sendMessage(Command cmd, float value, DataFormat format);
  void sendMessage(Command cmd, Parameter param, float value, DataFormat format);
  
};





#endif
