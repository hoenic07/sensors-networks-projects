#include "Bus.h"

//TODO: Everything

Bus::Bus(Thermometer* t, Accelerometer* a){
  thermometer = t;
  accelerometer = a;
}

Bus::~Bus(){
  
}

void Bus::sendMessage(){
  
    //Serial.write(incomingByte);
}

void Bus::receiveBytes(){
  bool serialAvailable = Serial.available();
  if(serialAvailable) {
    int incomingByte = readByte();

    if(incomingByte == MESSAGE_START_BYTE) {
      int length = readByte();

      if((length - 6)%2 != 0) {
        //invalid length
        //TODO handle case
        return;
      }

      BusMessage* message = new BusMessage();
      
      int messageBytes[length];
      messageBytes[0] = incomingByte;
      messageBytes[1] = length;

      //read message
      for(int i=2; i < length; i++) {
        messageBytes[i] = readByte();
      }
     
      message->length = length;
      message->receiver = messageBytes[2];

      //check command
      if(messageBytes[length - 1] != MESSAGE_END_BYTE || message->receiver != SENSOR) {
        //invalid message
        return;
      }
      
      message->command =  messageBytes[3];
      message->dataFormat = messageBytes[4];

      for(int i=5; i < length; i++) {
        message->data[i-5] = messageBytes[i];
      }

      //handle result
      processReceivedMessage(message);
    }
  }
}

int Bus::readByte(){
  while(!Serial.available()){
    delay(10);
  }
  return Serial.read();
}

void Bus::handleReceivedMessage(BusMessage msg){
  
}

void Bus::processReceivedMessage(BusMessage* msg) {
  //TODO check if epected response command

  if(msg != NULL) {
    Serial.write(msg->command);
    switch(msg->command) {
      case REQ_ACK: {
        sendMessage(ACK);
      }
      case REQ_TEMP:{
        double temp = thermometer->getTemperature();
        sendMessage(RESP_TEMP);
        break;
      }
      case REQ_X:{
        double x = accelerometer->getX();
        sendMessage(RESP_X, float(x), VALUE);
        break;
      break;
      }
      case REQ_Y:{
        double y = accelerometer->getY();
        sendMessage(RESP_Y, float(y), VALUE);
        break;
      break;
      }
      case REQ_Z:{
        
        Serial.write(3);
        double z = accelerometer->getZ();
        sendMessage(RESP_Z, float(z), VALUE);
        break;
      break;
      }
      //default: no need to handle other cases
    }
  }
}

BusMessage Bus::messageFromBytes(byte bytes[]){
  BusMessage msg;
  return msg;
}

void Bus::sendBusMessage(BusMessage* msg){
  int lenData = sizeof(msg->data)/sizeof(*msg->data);
  int len = 5 + lenData;
  
  Serial.write(MESSAGE_START_BYTE);
  Serial.write(len);
  Serial.write(msg->receiver);
  Serial.write(msg->command);
  Serial.write(msg->dataFormat);
  
  for(int i=0; i < lenData; i++) {
    Serial.write((byte)(msg->data[i]));
  }
  Serial.write(MESSAGE_END_BYTE);
}

void Bus::sendMessage(Command cmd, float value, DataFormat format) {
   BusMessage* msgToSend = new BusMessage();

   msgToSend->command = cmd;
   msgToSend->dataFormat = format;
   msgToSend->receiver = BUS;

   msgToSend->data[0] = (short)value;

   sendBusMessage(msgToSend);

   //TODO expected response
}

void Bus::sendMessage(Command cmd) {
   BusMessage* sendMessage = new BusMessage();

   sendMessage->command = cmd;
   sendMessage->dataFormat = NO_DATA;
   sendMessage->receiver = BUS;

   sendBusMessage(sendMessage);
}

void Bus::sendMessage(Command cmd, Parameter param, float value, DataFormat format) {
   BusMessage* sendMessage = new BusMessage();

   sendMessage->command = cmd;
   sendMessage->dataFormat = format;
   sendMessage->receiver = BUS;

   sendMessage->data[0] = param;
   sendMessage->data[1] =(short)value;

   //to bytes
   sendBusMessage(sendMessage);


   //TODO expected response
}

