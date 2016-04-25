#ifndef BUS_H
#define BUS_H

#include <StackArray.h>
#include "Arduino.h"
#include "Thermometer.h"
#include "Accelerometer.h"
#include "Parameters.h"

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
  REQ_ACK, //0
  REQ_TEMP,
  RESP_TEMP,
  REQ_X,
  REQ_Y,
  REQ_Z, //5
  REQ_PITCH,
  REQ_ROLL,
  REQ_THETA,
  RESP_X,
  RESP_Y, //10
  RESP_Z,
  RESP_PITCH,
  RESP_ROLL,
  RESP_THETA,
  REQ_PARA, //15
  RESP_PARA,
  SET_PARA,
  ALARM_TEMP,
  ALARM_ACC, //20
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

class Bus {
public:
  Bus(Thermometer* t, Accelerometer* a, Parameters* p);
  ~Bus();
  void receiveBytes();
  void sendMessage(Command cmd);
  void sendMessage(Command cmd, float value, DataFormat format);
  void sendMessage(Command cmd, Parameter param, float value, DataFormat format);
  const byte MESSAGE_START_BYTE = 0x55;
  const byte MESSAGE_END_BYTE = 0xAA;
private:
  int readByte();
  void sendBusMessage(BusMessage* msg);
  byte* receivedMessage;
  StackArray<int> receivedMessages;
  Thermometer* thermometer;
  Accelerometer* accelerometer;
  Parameters* parameters;
  void processReceivedMessage(BusMessage* msg);
};

#endif
