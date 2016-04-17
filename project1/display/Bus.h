#ifndef BUS_H
#define BUS_H

#include <StackArray.h>
#include "Arduino.h"


struct BusMessage{
  byte length;
  byte command;
  byte dataFormat;
  byte receiver;
  short data[2];
};


enum Receiver {
  NO_REC,
  BUS,
  SENSOR
};

enum DataFormat {
  NO_DF,
  NO_DATA,
  VALUE,
  PARAMETER, 
  PARAMETER_AND_VALUE, 
};

enum Parameter
{
  NO_PARAM,
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

//TODO: Define constants form command, dataFormat, receiver somewhere

class Bus {
public:
  Bus();
  ~Bus();
  void sendMessage();
  void receiveBytes();
  void handleReceivedMessage(BusMessage msg);
private:
  BusMessage messageFromBytes(byte bytes[]);
  int readByte();
  byte* messageToBytes(BusMessage msg);
  byte* receivedMessage;
  StackArray<int> receivedMessages;

  const int MESSAGE_START_BYTE = 0x55;
  const int COMMAND_REQ_ACK = 102;
  const int COMMAND_REQ_TEMP = 10;
  const int COMMAND_RESP_TEMP = 11;
  const int COMMAND_REQ_X = 20;
  const int COMMAND_REQ_Y = 21;
  const int COMMAND_REQ_Z = 22;
  const int COMMAND_RESP_X = 30;
  const int COMMAND_RESP_Y = 31;
  const int COMMAND_RESP_Z = 32;
  const int COMMAND_REQ_PARA = 40;
  const int COMMAND_RESP_PARA = 41;
  const int COMMAND_SET_PARA = 42;
  const int COMMAND_ALARM_TEMP = 50;
  const int COMMAND_ALARM_X = 60;
  const int COMMAND_ALARM_Y = 61;
  const int COMMAND_ALARM_Z = 62;
  const int COMMAND_RESET_MINMAX = 70;
  const int COMMAND_ACK = 100;
  const int COMMAND_NACK = 101;
  const int COMMAND_INVALID = 103 ;
};





#endif
