#include "Bus.h"

//TODO: Everything

Bus::Bus(){
  //Serial.begin(9600);
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
      
      //check command
     
      message->length = length;
      message->receiver = messageBytes[2];
      message->command =  messageBytes[3];
      message->dataFormat = messageBytes[4];
      
      
      for(int i=5; i < length; i++) {
        message->data[i-5] = messageBytes[i];
      }
    }
    //handle result
   
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

BusMessage Bus::messageFromBytes(byte bytes[]){
  BusMessage msg;
  return msg;
}

byte* Bus::messageToBytes(BusMessage msg){
  byte* bytes = new byte[10];
  return bytes;
}

