#include "Bus.h"

Bus::Bus(Thermometer* t, Accelerometer* a, Parameters* p){
  Serial.begin(9600);
  thermometer = t;
  accelerometer = a;
  parameters = p;
}

Bus::~Bus(){
  
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

      int dataLength = (length - 6)/2;
      
      for(int i=0; i < dataLength; i++) {
        byte lowB = messageBytes[5+i*2];
        byte highB = messageBytes[5+i*2+1];
        short combined = highB * 256 + lowB;
        message->data[i] = combined;
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

void Bus::processReceivedMessage(BusMessage* msg) {

  if(msg != NULL) {
    switch(msg->command) {
      case REQ_ACK: {
        sendMessage(ACK);
        break;
      }
      case REQ_TEMP:{
        double temp = thermometer->getTemperature();
        sendMessage(RESP_TEMP, temp, VALUE);
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
        double z = accelerometer->getZ();
        sendMessage(RESP_Z, float(z), VALUE);
        break;
      break;
      }
      case REQ_PITCH: {
        double pitch = accelerometer->getPitch();
        sendMessage(RESP_PITCH, float(pitch), VALUE);
        break;
      }
      case REQ_ROLL: {
         double roll = accelerometer->getRoll();
        sendMessage(RESP_ROLL, float(roll), VALUE);
        break;
      }
      case REQ_THETA: {
        double theta = accelerometer->getTheta();
        sendMessage(RESP_THETA, float(theta), VALUE);
        break;
      }
      case REQ_PARA:{
        Parameter p = (Parameter)msg->data[0];
        double val = parameters->getValue(p);
        sendMessage(RESP_PARA, p, val, PARAMETER_AND_VALUE);
        break;
      }
      case SET_PARA: {
        Parameter p = (Parameter)msg->data[0];
        double value = msg->data[1] / 100.0;
        parameters->setValue(p, value);
        sendMessage(ACK);

        if(p == CALIBRATION_TEMP) {
          thermometer->setCalibrationTemp(value);
        }
        
        break;
      }
      case RESET_MINMAX: {
        parameters->setMinMaxDefaultValues();
        sendMessage(ACK);
        break;
      }
      //default: no need to handle other cases
    }
  }
}

void Bus::sendBusMessage(BusMessage* msg){
  int lenData = 0;

  switch(msg->dataFormat){
    case NO_DATA:
      lenData=0;
      break;
    case VALUE:
    case PARAMETER:
      lenData=1;
      break;
    case PARAMETER_AND_VALUE:
      lenData=2; 
      break;
  }
  
  int len = 6 + lenData*2;

  byte buffer[20];
  
  buffer[0]= MESSAGE_START_BYTE;
  buffer[1]=len;
  buffer[2]=msg->receiver;
  buffer[3]=msg->command;
  buffer[4]=msg->dataFormat;
  
  for(int i=0; i < lenData; i++) {
    //get single bytes (2) out of short. WORKS!
    byte high = highByte(msg->data[i]);
    byte low = lowByte(msg->data[i]);
    buffer[5+i*2]=low;
    buffer[5+i*2+1]=high;
  }

  buffer[len-1]=MESSAGE_END_BYTE;
  
  Serial.write(buffer,len);
}

void Bus::sendMessage(Command cmd, float value, DataFormat format) {
   BusMessage* msgToSend = new BusMessage();

   msgToSend->command = cmd;
   msgToSend->dataFormat = format;
   msgToSend->receiver = BUS;

   msgToSend->data[0] = (short)(value*100);

   sendBusMessage(msgToSend);
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
   sendMessage->data[1] =(short)(value*100);

   //to bytes
   sendBusMessage(sendMessage);
}

