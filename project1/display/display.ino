// include the library code:
//#include "Instance.h"
#include "Display.h"
#include "Input.h"
#include "Thermometer.h"
#include "Monitor.h"
#include "Led.h"
#include "Bus.h"
#include "Accelerometer.h"

Display* display;
Thermometer* thermometer;
Input* input;
Led* led;
Monitor* monitor;
Parameters* parameters;
Accelerometer* accelerometer;
Bus* bus;
/*
#define txPin 2
#define yellowLedPin 13
#define redLedTempPin 12
#define tempBtnPin 7
#define AREF_VOLTAGE 3.3 
#define SCROLL_MAX_V 1023

int MIN_TEMP_C = 10;
int MAX_TEMP_C = 1024;

int minTempC = MAX_TEMP_C;
int maxTempC = MIN_TEMP_C;

int tempValue;

enum Line {
  CUR_TEMP,
  TEMP_MAX,
  TEMP_MIN,
  LINE_COUNT
};

const int numberOfLines = LINE_COUNT - 1;
const double SCROLL_INTERVALL = 100.1 / numberOfLines; 

SoftwareSerial LCD = SoftwareSerial(0, txPin);
SoftwareSerial YLED = SoftwareSerial(0, yellowLedPin);
SoftwareSerial RLED_TEMP = SoftwareSerial(0, redLedTempPin);

const int LCDdelay=100;  // conservative, 2 actually works

// wbp: goto with row & column
void lcdPosition(int row, int col) {
  LCD.write(0xFE);   //command flag
  LCD.write((col + row*64 + 128));    //position 
  delay(LCDdelay);
}
void clearLCD(){
  LCD.write(0xFE);   //command flag
  LCD.write(0x01);   //clear command.
  delay(LCDdelay);
}
void backlightOn() {  //turns on the backlight
  LCD.write(0x7C);   //command flag for backlight stuff
  LCD.write(157);    //light level.
  delay(LCDdelay);
}
/*
void backlightOff(){  //turns off the backlight
  LCD.write(0x7C);   //command flag for backlight stuff
  LCD.write(128);     //light level for off.
   delay(LCDdelay);
}
void serCommand(){   //a general function to call the command flag for issuing all other commands   
  LCD.write(0xFE);
}*/
/*
void showMinTemp() {
    LCD.print("Min: ");
    LCD.print(minTempC, DEC);
    LCD.print((char)223);
    LCD.print("C");
}

void showMaxTemp() {
  LCD.print("Max: ");
  LCD.print(maxTempC, DEC);
  LCD.print((char)223);
  LCD.print("C");
}

void showCurrentTemp() {
    LCD.print(tempValue, DEC);
    LCD.print((char)223);
    LCD.print("C");
}
*/
void setup()
{
 /* pinMode(txPin, OUTPUT);
  pinMode(yellowLedPin, OUTPUT);
  
  LCD.begin(9600);
  clearLCD();
  backlightOn();
  
  YLED.begin(9600);
  RLED_TEMP.begin(9600);*/
  display = new Display();
  input = new Input(display);
  led = new Led();
  parameters = new Parameters();
  monitor = new Monitor(led, parameters);
  thermometer = new Thermometer(display, monitor);
  accelerometer = new Accelerometer();
  bus = new Bus(thermometer, accelerometer);
  
  Serial.begin(9600);
}
/*
void showLine(Line line){
  switch(line) {
    case CUR_TEMP:
      showCurrentTemp();
      break;
    case TEMP_MIN:
      showMinTemp();
      break;
    case TEMP_MAX:
      showMaxTemp();
      break;
  }
}

Line prevTopLine;
Line topLine = CUR_TEMP;
*/
void loop()
{

  //Serial.println("Hello");

 /* if(digitalRead(7)==LOW){
    Serial.println("pressed");
  }else{
    Serial.println("no press");
  }*/

  bus->receiveBytes();

  thermometer->updateTemperature();
  input->checkInput();
  
  display->update();
  

  
  //serial port
  //Serial.print("S: ");
  /*Serial.write(1);
  bool serialAvailable = Serial.available();
  Serial.println(serialAvailable);
  if(serialAvailable) {
    int incomingByte = Serial.read();
    Serial.print("R: ");
    Serial.println(incomingByte, DEC);
    //Serial.write(incomingByte);
  }

  //scrolling
  double scrollInput = (double)analogRead(A1);
  int percentScrolling = scrollInput / SCROLL_MAX_V * 100;
  topLine = static_cast<Line>(percentScrolling / SCROLL_INTERVALL);
  
  if(prevTopLine != topLine){
    clearLCD();
  }
  prevTopLine = topLine;
  
  tempValue = analogRead(A0);

  float voltage = (tempValue * AREF_VOLTAGE) / 1024.0;
  //Serial.print(voltage); Serial.println(" volts");

  float temperatureC = (voltage - 0.5) * 100;
  //Serial.print(temperatureC); Serial.println(" degrees C");

  lcdPosition(0,0);
  showLine(topLine);
  lcdPosition(1,0);
  showLine(static_cast<Line>(topLine + 1));
  //clearLCD();

  //update measured min and max values
  if(temperatureC < minTempC) {
    minTempC = temperatureC;
  }
  if(temperatureC > maxTempC) {
    maxTempC = temperatureC;
  }

  //temp button reset
  if(digitalRead(tempBtnPin)==LOW){
    //button pressed -> reset values
    minTempC = 0;
    maxTempC = 0;
  }

  //max temperature reached -> ALARM (yellow LED)
  if(temperatureC > MAX_TEMP_C) {
    digitalWrite(yellowLedPin, HIGH);
  }else{
    digitalWrite(yellowLedPin, LOW);
  }

  //check if temp is out of range -> ALARM (red LED)
  if(temperatureC < MIN_TEMP_C || temperatureC > MAX_TEMP_C) {
    digitalWrite(redLedTempPin, HIGH);
  }else{
    digitalWrite(redLedTempPin, LOW);
  }

  */
  
  delay(1000);
}
