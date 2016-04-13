#ifndef BUS_H
#define BUS_H

#include "Arduino.h"

struct BusMessage{
  byte length;
  byte command;
  byte dataFormat;
  byte receiver;
  short data[2];
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
  byte* messageToBytes(BusMessage msg);
};





#endif
